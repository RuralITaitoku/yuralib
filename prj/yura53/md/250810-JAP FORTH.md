# JAP FORTH

## FORTHスタック操作
.	スタックのトップにある値をポップして表示します。	3 4 . -> 4
DUP	スタックのトップにある値を複製します。	3 DUP -> 3 3
DROP	スタックのトップにある値を削除します。	3 4 DROP -> 3
SWAP	スタックのトップにある2つの値の位置を入れ替えます。	3 4 SWAP -> 4 3
OVER	スタックのトップから2番目の値を複製し、スタックのトップに移動させます。	3 4 OVER -> 3 4 3
ROT	スタックのトップにある3つの値を循環的に移動させます。
## FORTHループ
- 5 0 DO I . LOOP

## FORTH条件分岐
- (flag -- ) IF ... THEN
- (flag -- ) IF ... ELSE ... THEN

## ループ
- body: 処理;
- body n loop
## 条件分岐
- true:  正解処理;
- false: 間違い処理
- :true :false (flag --) if

if: いろいろ ;
true: 正解 . ;
false: 間違い . ;

条件 :true :false if
条件 :true loop
