#include <iostream>
#include <string>

// Objective-Cのヘッダファイル
#import <AppKit/NSPasteboard.h>
#import <Foundation/NSString.h>

// Objective-C++を使用するため、このファイルは .mm 拡張子で保存する必要があります。
namespace hisa {

void copyToClipboard(const std::string& text) {
    // std::string を NSString に変換
    NSString* nsString = [NSString stringWithUTF8String:text.c_str()];

    // NSPasteboard の共有インスタンスを取得
    NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];

    // クリップボードの内容をクリア
    [pasteboard clearContents];

    // 文字列をクリップボードに書き込む
    // setString:forType: は成功した場合 YES を返します
    BOOL success = [pasteboard setString:nsString forType:NSPasteboardTypeString];

    if (success) {
        std::cout << "Successfully copied to clipboard: " << text << std::endl;
    } else {
        std::cerr << "Failed to copy to clipboard: " << text << std::endl;
    }
}
};

int main() {
    std::string myString = "これはmacOSのクリップボードにコピーされる文字列です。";
    hisa::copyToClipboard(myString);

    std::string anotherString = "Hello, Clipboard!";
    hisa::copyToClipboard(anotherString);

    return 0;
}