#pragma once
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"dxguid.lib")
#include <dsound.h>
#include <mmsystem.h>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include <mutex>
#include <thread>
#include <atomic>


/*
wavファイル再生用DirectSoundラッパークラス（シングルトン）

◆使用例
Audio& audio = Audio::getInterface(hWnd);		// 初期化時のみHWNDを必ず渡す
audio.load("hoge.wav");							// 単一ファイルの読み込み
audio.load({"foo.wav", "bar.wav"});				// 複数ファイルの一括読み込み

auto sound = audio.getBuffer("hoge.wav");		// サウンドバッファーの取得
sound->Play(0, 0, 0);							// 単純再生（頭出しはされない）
sound->Play(0, 0, DSBPLAY_LOOPING);				// ループ再生
sound->Stop();									// 停止
sound->SetCurrentPosition(0);					// 頭出し
sound->SetVolume(-1000);						// 音量調節（1/1000dB単位・負の値のみ）
*/
struct Audio {
	// 生のDirectSound8インターフェース（特殊な操作に使用）
	IDirectSound8* ds8 = NULL;

	// プライマリバッファ（全体の音量調節に使用可能）
	IDirectSoundBuffer* primary_buf = NULL;

	// シングルトンGetter
	// 注意：初回呼び出しは初期化を兼ねているため引数(HWND)を省略してはならない
	static Audio& getInterface(HWND hWnd = NULL) {
		static Audio a(hWnd);
		return a;
	}

	// 引数で指定したパスのwavファイルを読み込む
	IDirectSoundBuffer8* load(std::string file_path) {
		auto itr = list.find(file_path);
		if (itr != list.end()) {
			return itr->second;
		}

		HMMIO hMmio = nullptr;

		MMIOINFO mmioInfo = {};
		hMmio = mmioOpen((LPSTR)file_path.c_str(), &mmioInfo, MMIO_READ);
		if (!hMmio) {
			std::string msg = file_path + "のオープンに失敗";
			MessageBox(NULL, msg.c_str(), NULL, MB_OK);
			return NULL;
		}

		MMRESULT mmRes;

		MMCKINFO riffChunk;
		riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
		if (mmRes != MMSYSERR_NOERROR) {
			mmioClose(hMmio, 0);
			return NULL;
		}

		MMCKINFO formatChunk;
		formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
		if (mmRes != MMSYSERR_NOERROR) {
			mmioClose(hMmio, 0);
			return NULL;
		}

		WAVEFORMATEX format;
		DWORD fmsize = formatChunk.cksize;
		if (mmioRead(hMmio, (HPSTR)&format, fmsize) != fmsize) {
			mmioClose(hMmio, 0);
			return NULL;
		}

		mmioAscend(hMmio, &formatChunk, 0);

		MMCKINFO dataChunk;
		dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
		if (mmRes != MMSYSERR_NOERROR) {
			mmioClose(hMmio, 0);
			return NULL;
		}

		DWORD data_size = dataChunk.cksize;
		BYTE* data = new BYTE[dataChunk.cksize];
		if (mmioRead(hMmio, (HPSTR)data, dataChunk.cksize) != dataChunk.cksize) {
			delete data;
			return NULL;
		}

		mmioClose(hMmio, 0);

		DSBUFFERDESC desc = {
			sizeof(DSBUFFERDESC),
			DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY,
			data_size,
			0,
			&format,
			GUID_NULL
		};

		IDirectSoundBuffer* buf;
		IDirectSoundBuffer8* buf8;
		ds8->CreateSoundBuffer(&desc, &buf, NULL);
		buf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&buf8);
		buf->Release();

		LPVOID data_dst;
		DWORD len;
		buf8->Lock(0, 0, &data_dst, &len, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		memcpy(data_dst, data, len);
		buf8->Unlock(data_dst, len, NULL, 0);
		delete[] data;

		list.emplace(file_path, buf8);

		return buf8;
	}

	// 一括読み込み
	void load(std::initializer_list<std::string> file_path) {
		for (auto& it : file_path) {
			load(it);
		}
	}

	// 再生・停止・音量変更等を行うためのインタフェースを返す
	IDirectSoundBuffer8* getBuffer(std::string file_path) const {
		auto itr = list.find(file_path);
		if (itr != list.end()) {
			return itr->second;
		}
		return NULL;
	}

	// 単一音源多重再生用（解放処理を自前で行う必要あり）
	IDirectSoundBuffer8* getCloneBuffer(std::string file_path) {
		auto itr = list.find(file_path);
		if (itr != list.end()) {
			IDirectSoundBuffer8* sb;
			ds8->DuplicateSoundBuffer(itr->second, (IDirectSoundBuffer**)&sb);
			mux.lock();
			clone.push_back(sb);
			mux.unlock();
			return sb;
		}
		return NULL;
	}


private:
	std::unordered_map<std::string, IDirectSoundBuffer8*> list;

	std::mutex mux;
	std::vector<IDirectSoundBuffer8*> clone;

	std::atomic_int loop;

	Audio(HWND hWnd) {
		DirectSoundCreate8(NULL, &ds8, NULL);
		ds8->SetCooperativeLevel(hWnd, DSSCL_NORMAL);

		DSBUFFERDESC desc = {
			sizeof(DSBUFFERDESC),
			DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME,
			0,
			0,
			NULL,
			GUID_NULL
		};
		ds8->CreateSoundBuffer(&desc, &primary_buf, NULL);

		loop = 1;
		std::thread([&] {
			while (loop == 1) {
				if (mux.try_lock()) {
					for (auto itr = clone.begin(); itr != clone.end();) {
						DWORD status;
						if ((*itr)->GetStatus(&status) == DS_OK) {
							if ((status & DSBSTATUS_PLAYING) == 0) {
								(*itr)->Release();
								itr = clone.erase(itr);
							}
							else {
								++itr;
							}
						}
					}
					mux.unlock();
				}

				Sleep(1);
			}
			loop = 0;
		}).detach();
	}

	~Audio() {
		for (auto& it : list) {
			while (it.second->Release() != 0);
		}

		loop = 2;
		do {
			Sleep(10);
		} while (loop == 2);

		ds8->Release();
	}

	Audio(const Audio&) = delete;
};
