# `src/core/init.h` 詳細解説

## 概要
ゲーム初期化に関連する内部関数のプロトタイプ宣言を提供します。

## 詳細は以下を参照
*   [`src/core/game_init.c.md`](./game_init.c.md) - `init_parse`
*   [`src/parser/parse_player.c.md`](../parser/parse_player.c.md) - `init_player_dir` (※実装箇所により異なる場合あり。`parse_player.c` の `set_direction` に相当する可能性があります)

## コード行別解説

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 18 | `void init_parse(t_game *game);` | 初期化変数のセットアップ関数。 |
| 19 | `void init_player_dir(t_game *game);` | プレイヤーの向きの初期化関数。 |
