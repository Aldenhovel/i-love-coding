// 泛型函数
function fn<T>(item: T): T {
    return item;
}
fn(19); // 自动推断机制可以知道类型
fn<string>("hello world");  // 更好的写法是指定类型

// 多个泛型
function fn2<T, K>(item1: T, item2: K): [T, K] {
    return [item1, item2];
}

// 泛型类
class Item<T> {
    public item: T;
    constructor(item: T) {
        this.item = item;
    }
}

// 数组泛型
let arr: Array<number> = [1, 2, 3];
console.log(typeof arr[0]);
for (const i in arr) {
    console.log(i);
}