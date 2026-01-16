# `src/engine/raycast.h` 詳細解説

## 概要
レイキャスティングエンジン内部で使用される関数のプロトタイプ宣言です。`raycast.c` と `raycast_utils.c` で共有されます。

## 詳細は以下を参照
*   [`src/engine/raycast_utils.c.md`](./raycast_utils.c.md)

## コード行別解説

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 18 | `void perform_dda(t_game *game);` | DDAアルゴリズム実行関数。 |
| 19 | `void select_texture(...);` | テクスチャ選択関数。 |
| 20-21 | `void init_ray_step_...` | レイのステップ初期化関数。 |
