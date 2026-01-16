# `src/parser/parse_map.c` 詳細解説

## 概要
設定要素のパースが終わった後の行から、ファイル末尾までをマップデータとして読み込みます。マップの幅と高さを計算し、各行の長さを最大幅に合わせてスペースで埋める（正規化）処理を行い、長方形のグリッドデータ `game->map.grid` を作成します。

## 依存関係
*   `parse.h`: パース用ヘッダ。
*   `libft.h`: `ft_strlen`, `ft_memcpy`, `ft_memset` 等。

## 関数詳細

### 1. `process_map_line`
#### プロトタイプ
`static int process_map_line(char *line, char ***temp_map, int *height, int *max_width, int *map_ended)`

#### 戻り値
*   `1`: 正常処理。
*   `0`: エラー（マップ途中の空行など）。

#### 解説
読み込んだ1行をマップの一部として処理します。
*   空行の場合：マップ開始前なら無視、マップ途中なら「マップ終了フラグ」を立てます。
*   行末の改行削除、最大幅の更新を行い、`change_line_to_map`（`realloc`的な処理）で配列に追加します。

#### コード行別解説 (`process_map_line`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 19-24 | `if (is_empty_line(line))` | **空行処理**<br>空行が見つかった場合、既にマップ行を読んでいる（`height > 0`）なら「マップ終了」とみなしフラグを立てます。 |
| 25-28 | `if (*map_ended)` | **分割マップ検知**<br>既に「マップ終了」フラグが立っているのに、さらにマップ行（非空行）が現れた場合、マップが空行で分断されている不正な状態なのでエラー(`0`)を返します。 |
| 29 | `cleanup_line(line);` | 行末の改行コードを削除します。 |
| 31-32 | `if (*max_width < current_width)` | 最大幅を更新します（正規化時に使用）。 |
| 33 | `*temp_map = change_line_to_map(...)` | 現在の行を一時マップ配列に追加（拡張）します。 |

### 2. `normalize_map`
#### プロトタイプ
`static int normalize_map(t_game *game, char **temp_map, int height, int max_width)`

#### 戻り値
*   `1`: 成功。
*   `0`: メモリ確保失敗。

#### 解説
マップの各行の長さを揃えるために、短い行の後ろにスペースを埋めます。すべての行が `max_width` の長さを持つ長方形の配列（2次元配列）に変換します。これにより、後の処理でインデックス外参照を防ぎやすくなります。

#### コード行別解説 (`normalize_map`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 48 | `while (i < height)` | 全行に対してループ処理を行います。 |
| 49 | `new_row = malloc(max_width + 1);` | 最大幅分のメモリを新しく確保します。 |
| 52 | `ft_memset(new_row, ' ', max_width);` | **スペース埋め**<br>確保した領域全体をスペースで初期化します。 |
| 54 | `ft_memcpy(new_row, temp_map[i], ...);` | 元の行の内容をコピーします。短い行の場合、残りの部分はスペースのままになります。 |
| 55-56 | `free(temp_map[i]); temp_map[i] = new_row;` | 元の行を解放し、正規化した行に差し替えます。 |
| 59-61 | `game->map.grid = temp_map;` | 完成したマップ配列をゲーム構造体に保存します。 |

### 3. `read_lines`
#### プロトタイプ
`static int read_lines(int fd, char ***temp_map, int *height, int *max_width, char *first_line)`

#### 戻り値
*   `1`: 読み込み成功。
*   `0`: 読み込み中エラー（`process_map_line` のエラー）。

#### 解説
`get_next_line` をループさせ、ファイルの最後まで読み込みます。各行に対して `process_map_line` を呼び出します。

#### コード行別解説 (`read_lines`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 71 | `line = first_line;` | 呼び出し元から渡された最初の1行目から開始します。 |
| 72 | `while (line)` | EOF（`line` が `NULL`）になるまでループします。 |
| 73 | `if (!process_map_line(...))` | 行処理に失敗（分割マップ等）したらループを抜け、エラーを返します。 |
| 78 | `line = get_next_line(fd);` | 次の行を読み込みます。 |

### 4. `parse_map`
#### プロトタイプ
`int parse_map(int fd, t_game *game, char *first_line)`

#### 戻り値
*   `1`: マップパース成功。
*   `0`: 失敗。

#### 解説
`read_lines` で全行読み込んで一時配列を作成し、その後 `normalize_map` で整形して `t_game` にセットします。

#### コード行別解説 (`parse_map`)

| 行番号 | コード | 詳細解説 |
| :--- | :--- | :--- |
| 91 | `if (!read_lines(...))` | **行読み込み**<br>ファイルの残りを全て読み込みます。途中に空行が入る「分割マップ」などのエラーもここで検知されます。 |
| 94-98 | `if (height == 0)` | マップ行が1行もなかった場合（設定だけでファイルが終わっている場合）、エラーにします。 |
| 99 | `if (!normalize_map(...))` | **マップ正規化**<br>ガタガタの行長を揃えます。 |
| 104 | `return (1);` | 成功。 |
