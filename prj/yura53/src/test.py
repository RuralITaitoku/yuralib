import tkinter as tk
from tkinter import font

# �t�H���g�̎w��
# Windows�̏ꍇ
font_name = "Yu Gothic UI"

# 1. ���[�g�E�B���h�E���쐬
root = tk.Tk()
root.title("���߂Ă�GUI")  # �E�B���h�E�̃^�C�g����ݒ�
root.geometry("300x200") # �E�B���h�E�̃T�C�Y��ݒ�

# �t�H���g�t�@�~���[�ƃT�C�Y���w��
jap_font = font.Font(family=font_name, size=20)

# 2. ���x���E�B�W�F�b�g���쐬
label = tk.Label(root, text="����ɂ��́I", font=jap_font)
label.pack(pady=20)  # �E�B���h�E�̒����ɔz�u

# 3. �C�x���g���[�v���J�n
root.mainloop()



