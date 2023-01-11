# TypeScript

存放 TypeScript 的相关代码仓库，因为不常用所以整理成笔记防止忘记。目录里面一般存放一个 `.ts` 源文件和一个编译后的 `.js` 目标文件。

## 指南

|     目录     |                描述                |
| :----------: | :--------------------------------: |
| `chapter_01` |            基本变量类型            |
| `chapter_02` | 关于对象内部的类型限制、数组、枚举 |
| `chapter_03` |            面向对象，类            |
| `chapter_04` |          类的继承、抽象类          |

## 安装

安装 TypeScript 需要保证：

- Node.js 安装

- TypeScript 安装

  ```shell
  npm install typescript -g
  ```

## 编译相关设置

使用编译器将 `.ts` 文件自动编译为 `.js` 文件：

```shell
cd path 			# 或在目录下打开终端
tsc filename.ts		# 编译对应 ts 文件
tsc					# 编译所有 ts 文件
```

使用 `-w` 参数可以让编译器监视 `ts` 文件变化来实时编译为 `js` 代码：

```shell
tsc filename.ts -w 
```

使用 `tsconfig.json` 来配置更详细的编译设置：

- `"include": [dir_path, ...]` 包含哪些目录
- `"exclude": [dir_path, ...]` 不包含哪些目录
- `"files": [file_path, ...]` 包含哪些单个文件
- `"compilerOptions"`
  - `"target": "es5",` 编译目标如 比较新的"es6" 对老浏览器支持较好的"es3" 最新"es2020" 等
  - `"module": "commonjs"` 编译的模块化标准如"commonjs" "es6" 等
  - `"lib": []` 使用的库如 "dom" ，一般不动
  - `"outDir": "./dist"` 编译输出的文件位置，有时项目需要将 src 和 dist 分开
  - `"outFile": "./dist/app.js" ` 可以将编译后的所有目标合并到一起，但只能支持 module 为 amd 或 system
  - `"allowJs": false` 是否编译 js 文件，默认 false 会跳过目录下的 js 文件
  - `"checkJs": false` 是否顺便检查 js 文件语法规范
  - `"removeComments": true` 移除 ts 的注释，默认为 true
  - `"noEmit":false` 不生成编译文件（但是编译过程还是会正常进行，只是不输出文件）
  - `"noEmitOnError": false` 编译出错时不产生编译文件

```json
{
  "compilerOptions": {
    "module": "commonjs",
    "target": "es5",
    "sourceMap": true
  },
  "exclude": [
    "node_modules"
  ]
}
```

在有 `tsconfig.json` 文件的目录下使用：

```shell
tsc
```

即可按照设置编译。

