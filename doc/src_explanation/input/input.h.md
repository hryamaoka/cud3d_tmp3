# `src/input/input.h` 詳細解説

## 概要
入力処理およびプレイヤーアクションに関連する定数と関数プロトタイプを定義します。

## 定数定義
*   `ROT_SPEED` (0.05): 回転速度（ラジアン）。約2.8度。
*   `MOVE_SPEED` (0.1): 移動速度（グリッド単位）。
*   `COLLISION_BUFFER` (0.2): 壁との衝突判定における余裕距離。

## 詳細は以下を参照
*   [`src/input/movement.c.md`](./movement.c.md)
*   [`src/input/rotate.c.md`](./rotate.c.md)
*   [`src/input/action.c.md`](./action.c.md)

## コード行別解説

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 22-25 | `void move_...` | 前後左右への移動関数。 |
| 26-27 | `void rotate_...` | 左右回転関数。 |
| 28 | `void interact_door(...);` | ドア操作関数。 |
