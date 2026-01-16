# `src/render/render.h` 詳細解説

## 概要
描画エンジン、特にミニマップやスプライト処理で使用される定数、構造体、関数プロトタイプを定義します。

## 定数・構造体
*   **ミニマップ設定**: `MM_SCALE` (12px), `MM_OFFSET` (10px), 各種カラーコード。
*   `t_sprite_vars`: スプライト描画計算に使用する一時変数をまとめた構造体（引数を減らすために使用）。

## 詳細は以下を参照
*   [`src/render/minimap.c.md`](./minimap.c.md)
*   [`src/render/sprite.c.md`](./sprite.c.md)
*   [`src/render/sprite_utils.c.md`](./sprite_utils.c.md)

## コード行別解説

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 28-38 | `struct s_sprite_vars` | スプライト計算用変数の構造体定義。座標変換結果や描画範囲などを保持します。 |
| 44-45 | `draw_minimap`, `draw_sprites` | 各描画コンポーネントのエントリーポイント。 |
