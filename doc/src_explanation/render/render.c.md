# `src/render/render.c` 詳細解説

## 概要
フレームごとの描画処理を統括します。天井と床の塗りつぶし、計算された情報に基づくテクスチャ付きの壁描画、そして最終的な画像のウィンドウへの転送を行います。

## 依存関係
*   `render.h`: 描画関連関数定義。
*   `mlx.h`: `mlx_put_image_to_window`。

## 関数詳細

### 1. `draw_ceiling`
#### プロトタイプ
`static void draw_ceiling(t_game *game, int x, int draw_start)`

#### 戻り値
なし

#### 解説
画面最上部から壁の描画開始位置までを、天井色で塗りつぶします。

#### コード行別解説 (`draw_ceiling`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 20 | `while (y < draw_start)` | **塗りつぶしループ**<br>Y座標0から壁の開始点までループします。 |
| 21 | `pixel = (y * game->img.line_length) ...` | **メモリアドレス計算**<br>描画バッファ内のピクセル位置（インデックス）を計算します。`(y * 行幅) + (x * ピクセル幅)`。 |
| 22-24 | `game->img.addr[pixel] = ...` | **色代入**<br>メモリに直接BGR順で色のバイト値を書き込みます（リトルエンディアン環境を想定）。 |

### 2. `draw_floor`
#### プロトタイプ
`static void draw_floor(t_game *game, int x, int draw_end)`

#### 戻り値
なし

#### 解説
壁の描画終了位置から画面最下部までを、床色で塗りつぶします。

#### コード行別解説 (`draw_floor`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 33 | `y = draw_end;` | **開始位置**<br>壁の終わりから描画を開始します。 |
| 34 | `while (y < game->img.height)` | **塗りつぶしループ**<br>画面下端（height）までループします。 |
| 36-38 | `game->img.addr[pixel] = ...` | 天井と同様に、床の色を書き込みます。 |

### 3. `draw_floor_ceiling`
#### プロトタイプ
`void draw_floor_ceiling(t_game *game, int x, int draw_start, int draw_end)`

#### 戻り値
なし

#### 解説
`draw_ceiling` と `draw_floor` を順に呼び出すラッパー関数です。特定の列 `x` の背景処理を完了させます。

#### コード行別解説 (`draw_floor_ceiling`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 44 | `draw_ceiling(game, x, draw_start);` | 壁より上の領域を天井色で描画します。 |
| 45 | `draw_floor(game, x, draw_end);` | 壁より下の領域を床色で描画します。 |

### 4. `draw_textured_line`
#### プロトタイプ
`void draw_textured_line(t_game *game, int x, int *draw, t_img *tex, int tex_x)`

#### 戻り値
なし

#### 解説
計算された壁の範囲（`draw[0]` 〜 `draw[1]`）に、指定されたテクスチャ `tex` の列 `tex_x` を貼り付けます。

#### コード行別解説 (`draw_textured_line`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 55 | `step = 1.0 * tex->height / ...` | **ステップ計算**<br>テクスチャの高さを壁の描画高さで割ることで、スケーリング比率を求めます。 |
| 56 | `tex_pos = ...` | **初期位置**<br>描画開始点に対応するテクスチャ上のY座標を計算します。壁が画面からはみ出している場合も考慮されています。 |
| 58 | `while (y < draw[1])` | **描画ループ**<br>画面上の指定範囲をピクセルごとに塗ります。 |
| 59 | `tex_y = (int)tex_pos & (tex->height - 1);` | **Y座標取得**<br>現在の位置を整数化します。`& (height - 1)` は `% height` の高速化（ただし高さが2の累乗である必要があります）として機能し、座標のループやオーバーフローを防ぎます。 |
| 63-67 | `game->img.addr[idx] = ...` | **ピクセル書込**<br>テクスチャから取得した色を、画面バッファの対応する位置に書き込みます。 |

### 5. `render_frame`
#### プロトタイプ
`int render_frame(t_game *game)`

#### 戻り値
常に `0`。

#### 解説
`mlx_loop_hook` に登録されるメイン描画関数です。毎フレーム呼び出されます。

#### コード行別解説 (`render_frame`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 74 | `raycast(game);` | **レイキャスト実行**<br>全画面の壁描画位置を計算し、背景（床・天井）と壁を描画バッファに書き込みます。 |
| 75 | `draw_sprites(game);` | **スプライト描画**<br>Zバッファを参照しながら、壁の手前にあるスプライトを上書き描画します。 |
| 76 | `draw_minimap(game);` | **ミニマップ描画**<br>画面の隅に2Dマップを上書きします。 |
| 77 | `mlx_put_image_to_window(...);` | **画面更新**<br>完成した描画バッファ(`game->img`)をウィンドウに転送・表示します。 |
| 78 | `game->frame_count++;` | フレームカウンタを更新します（デバッグやアニメーション用）。 |
