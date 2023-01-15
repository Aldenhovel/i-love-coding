// 泛型函数
function fn(item) {
    return item;
}
fn(19); // 自动推断机制可以知道类型
fn("hello world"); // 更好的写法是指定类型
// 多个泛型
function fn2(item1, item2) {
    return [item1, item2];
}
// 泛型类
var Item = /** @class */ (function () {
    function Item(item) {
        this.item = item;
    }
    return Item;
}());
// 数组泛型
var arr = [1, 2, 3];
console.log(typeof arr[0]);
for (var i in arr) {
    console.log(i);
}
