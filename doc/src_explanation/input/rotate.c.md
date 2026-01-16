# `src/input/rotate.c` 詳細解説

## 概要
プレイヤーの視点（方向ベクトルとカメラ平面ベクトル）を回転させます。キーボードによる回転と、マウス移動による回転の両方をサポートします。

## 依存関係
*   `input.h`: `ROT_SPEED` 定数。
*   `<math.h>`: `sin`, `cos` 関数。

## 関数詳細

### 1. `rotate_player`
#### プロトタイプ
`void rotate_player(t_game *game, double angle)`

#### 戻り値
なし

#### 解説
回転行列を用いて、方向ベクトル `(dir_x, dir_y)` とカメラ平面ベクトル `(plane_x, plane_y)` を `angle` ラジアンだけ回転させます。
公式:
```
new_x = x * cos(θ) - y * sin(θ)
new_y = x * sin(θ) + y * cos(θ)
```

### 2. `rotate_left` / `rotate_right`
定数 `ROT_SPEED` を使って `rotate_player` を呼び出します。

### 3. `mouse_handler`
#### プロトタイプ
`int mouse_handler(int x, int y, t_game *game)`

#### 戻り値
常に `0`。

#### 解説
マウスのX座標の変化量を検知し、それに応じて視点を回転させます。
処理後、`mlx_mouse_move` でマウスカーソルをウィンドウ中央に戻すことで、無限に回転操作ができるようにします（FPSゲームのような操作感）。

### コード行別解説 (`rotate_player`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 20-21 | `old_dir_x = ...` | **退避**<br>計算中に値が更新されてしまうため、元の値を一時変数に保存しておきます。 |
| 22-24 | `game->player.dir_x = ...` | **回転計算**<br>回転行列の公式を適用して新しい向きを計算します。 |
| 25-28 | `game->player.plane_x = ...` | **カメラ平面回転**<br>視野（FOV）を維持するために、カメラ平面ベクトルも同じ角度だけ回転させる必要があります。これを忘れると視界が歪みます。 |
