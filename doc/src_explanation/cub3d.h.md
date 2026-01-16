# `include/cub3d.h` 詳細解説

## 概要
プロジェクト全体で使用される主要なデータ構造体（構造体）と関数プロトタイプ宣言をまとめた共通ヘッダーファイルです。各ソースファイルはこのヘッダーをインクルードすることで、定義された型や関数を利用できます。

## 依存関係
*   `ft_printf.h`: ログ出力用（自作printf）。
*   `get_next_line.h`: ファイル読み込み用。
*   `libft.h`: 文字列操作やメモリ操作用。
*   `mlx.h`: MiniLibXグラフィックライブラリ。
*   `<math.h>`, `<stdlib.h>` 等: 標準ライブラリ。

## コード行別解説

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 13-14 | `#ifndef CUB3D_H`, `#define CUB3D_H` | **インクルードガード**<br>このファイルが複数回インクルードされて定義が重複するのを防ぎます。 |
| 27-32 | `typedef struct s_tex { ... } t_tex;` | **テクスチャパス構造体**<br>東西南北の各壁テクスチャのファイルパスを保持します（NO, SO, WE, EA）。 |
| 34-38 | `typedef struct s_color { ... } t_color;` | **色情報構造体**<br>RGB値を保持します。天井や床の色指定に使用されます。 |
| 40-44 | `typedef struct s_map { ... } t_map;` | **マップ構造体**<br>`grid`: マップの文字配列（2次元配列）。<br>`width`, `height`: マップの幅と高さ。 |
| 46-54 | `typedef struct s_player { ... } t_player;` | **プレイヤー構造体**<br>`x`, `y`: 現在位置。<br>`dir_x`, `dir_y`: 向いている方向ベクトル。<br>`plane_x`, `plane_y`: カメラ平面（視野）ベクトル。<br>`direction`: 初期向きを示す文字（N, S, E, W）。 |
| 56-74 | `typedef struct s_ray { ... } t_ray;` | **レイキャスティング用構造体**<br>計算中に使用される変数をまとめています。<br>`ray_dir`: 光線の方向。<br>`map_x`, `map_y`: 現在チェック中のマップ座標。<br>`side_dist`: 次の境界線までの距離。<br>`delta_dist`: 1マス進むごとの距離増加量。<br>`perp_wall_dist`: 壁までの垂直距離（魚眼補正済み）。<br>`hit`, `side`: 壁ヒット有無とヒットした面（縦/横）。 |
| 76-84 | `typedef struct s_img { ... } t_img;` | **MLX画像構造体**<br>MiniLibXの画像データを管理します。<br>`img`: 画像ポインタ。<br>`addr`: ピクセルデータへのアドレス。<br>`bits_per_pixel`, `line_length`, `endian`: 画像メタデータ。 |
| 86-89 | `typedef struct s_sprite { ... } t_sprite;` | **スプライト構造体**<br>マップ上のオブジェクト（アイテム等）の位置情報を保持します。 |
| 91-113 | `typedef struct s_game { ... } t_game;` | **ゲームメイン構造体**<br>ゲーム全体の情報を統括する巨大な構造体です。<br>`mlx`, `win`: MLXのポインタ。<br>`tex`, `floor`, `ceiling`: パースされた設定情報。<br>`map`, `player`: マップとプレイヤー情報。<br>`z_buffer`: 奥行き判定用のバッファ。<br>`sprites`: スプライトの配列。<br>`wall_tex`, `door_tex`, `sprite_tex`: 読み込まれたテクスチャ画像データ。 |
| 115-138 | `void init_game(...)` 等 | **関数プロトタイプ宣言**<br>各ソースファイルで実装されている関数の宣言一覧です。これにより、どのファイルからでもこれらの関数を呼び出せます。 |
