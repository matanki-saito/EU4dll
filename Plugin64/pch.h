// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

// プリコンパイルするヘッダーをここに追加します
#include "framework.h"
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <filesystem>
#include <list>
#include <map>
#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>       // for std::shared_ptr
#include <tuple>
#include <cstdio>
#include <boost/utility/string_view.hpp>
#include <boost/algorithm/string.hpp>
#include "byte_pattern.h"
#include "injector.hpp"


#endif //PCH_H
