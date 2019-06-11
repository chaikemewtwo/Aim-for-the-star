#include"Msg.h"
#include"../StarFish_Project/Lib/Window/Window.h"

/* メッセージ処理 */

namespace Msg {

	void ErrorMessage(const std::string&error_message, const std::string&message_box_name) {

		// unicode対応のメッセージボックス使用
		MessageBoxA(Window::GetWindowHandle(), error_message.c_str(), message_box_name.c_str(), MB_OK);
	}
}
