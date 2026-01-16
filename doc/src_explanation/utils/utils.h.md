# `src/utils/utils.h` 詳細解説

## 概要
プロジェクト全体で共有されるユーティリティ関数（エラー処理、メモリ解放、数学関数など）のプロトタイプ宣言です。

## 詳細は以下を参照
*   [`src/core/error.c.md`](../core/error.c.md) - `perror_and_exit`
*   [`src/core/game_cleanup.c.md`](../core/game_cleanup.c.md) - `free_all`, `free_split`
*   [`src/utils/utils.c.md`](./utils.c.md) - `ft_abs`

## コード行別解説

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 18 | `ft_abs` | 整数絶対値関数。 |
| 19 | `perror_and_exit` | エラー出力・終了関数。 |
| 20-21 | `free_all`, `free_split` | メモリ解放関数。 |
