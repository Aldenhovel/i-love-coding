# 使用 Webstorm 开发 Vuejs 项目相关备忘录

## 1 安装 Webstorm

1. 下载应用程式并安装：[WebStorm Offical](https://www.jetbrains.com/webstorm/) 并激活。

## 2 安装 Node.js

1. 下载安装文件并安装：[Node.js Offical](http://nodejs.cn/download/)  。

2. 在控制台检查 `node` `npm` 安装结果：

   ```shell
   node -v
   npm -v
   ```

3. 最好把 `cnpm` 也安装：

   ```shell
   npm install cnpm -g
   ```

## 3 安装 Vue 及相关组件

1. 控制台：

   ```shell
   cnpm install vue
   cnpm install --global vue-cli
   ```

2. 检查：

   ```shell
   vue -V
   ```

   这里需要注意安装的 `vue` 版本是否高于 `3.0` 因为很多功能需要版本高于 `3.0` 才支持，但有时默认安装的是 `2.9.6` ，这时需要卸载重装：

   ```shell
   npm uninstall vue/cli -g
   npm i -g --force @vue/cli
   vue -V
   ```

3. 启动图形界面

   ```shell
   vue ui
   ```

   ![image-20230104170609043](img/image-20230104170609043.png)

