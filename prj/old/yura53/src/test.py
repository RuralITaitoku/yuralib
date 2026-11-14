import tkinter as tk
from tkinter import font

# フォントの指定
# Windowsの場合
font_name = "Yu Gothic UI"

# 1. ルートウィンドウを作成
root = tk.Tk()
root.title("初めてのGUI")  # ウィンドウのタイトルを設定
root.geometry("300x200") # ウィンドウのサイズを設定

# フォントファミリーとサイズを指定
jap_font = font.Font(family=font_name, size=20)

# 2. ラベルウィジェットを作成
label = tk.Label(root, text="こんにちは！", font=jap_font)
label.pack(pady=20)  # ウィンドウの中央に配置

# 3. イベントループを開始
root.mainloop()



