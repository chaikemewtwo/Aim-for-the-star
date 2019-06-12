#include"Msg.h"
#include"../"

/* メッセージ処理 */

namespace Msg {

	void ErrorMessage(const std::string&error_message, const std::string&message_box_name) {

		// unicode対応のメッセージボックス使用
		MessageBoxA(Window::GetWindowHandle(), error_message.c_str(), message_box_name.c_str(), MB_OK);
	}
}
