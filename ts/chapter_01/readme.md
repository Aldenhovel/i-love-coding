# Chapter 01 变量

## 1 静态变量

类型检查是 TypeScript 的重点功能之一，他会在编译为 `js` 之前对语法进行类型检查，严格控制为静态变量。

```ts
let a: string = "hello world";	// 合法
let b: string = 12;				// 不合法
let c = false;					// 合法，且自动指定 c 为 boolean 静态类型
```

## 2 静态函数参数变量

可以对函数参数和返回值作出类型限制：

```ts
function sum(a: number, b: number): number {
    return a + b;
}

let res: number = sum(12, 34);
console.log(res)
```

## 3 基本类型目录

### 3.1 number

```ts
let a: number = 10;
```

### 3.2 string

```typescript
let s: string = "hello world";
```

### 3.3 boolean

```typescript
let b: boolean = false;
```

### 3.4 字面量

```ts
let a: 10;	// 相当于 const 不能再修改
let sex: "male" | "female"	// 相当于 enum 可以设置为其中之一
```

### 3.5 any

```typescript
let d: any;		// 设置 any 相当于关闭类型检查，不建议使用
let d;			// 不指定类型时等于 any 类型
d = 10;			// OK
d = "hello";	// OK
```

### 3.6 unknown



