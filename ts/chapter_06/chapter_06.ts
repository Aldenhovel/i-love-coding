// if else
let a: number = 10;
if (a < 10) {
    console.log("a < 10");
} else if (a < 20) {
    console.log("10 <= a < 20")
} else {
    console.log("a > 20");
}

// for
for (let i=0; i < 10; i++) {
    console.log(i);
}

// for in
let arr: Array<number> = [11, 22]
for (let num in arr) {
    console.log(num);
}

// for of
// 除了支持 Array 还支持 String Map Sets 等数据结构的遍历
let str: string = "Hello";
for (let char of str) {
    console.log(char);
}

// forEach
let arr1: Array<number> = [12, 34, 556];
arr1.forEach(function (value, index, array) {
    console.log(value);
})

// every
// 比较推荐用 .every 而非 .forEach 这里是对整个 Array 各个元素做判断，非 filter 或者 map 操作，因此返回 boolean
let res: boolean = arr1.every((value, index, array) => {
    return value > 20;
})
console.log(`${arr1} == every element > 20? == ${res}`)

// filter
let filterArr: Array<number> = arr1.filter((value, index, array) => {
    return value > 20;
})
console.log(`${arr1} == filter element > 20 == ${filterArr}`);

// map
let mapArr: Array<number> = arr1.map((value, index, array) => {
    return value + 1;
})
console.log(`${arr1} == map element += 1 == ${mapArr}`);


