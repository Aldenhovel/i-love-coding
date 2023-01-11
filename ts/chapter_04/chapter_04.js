var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
// 以 Animal 为抽象类基类，abstract 抽象类只能用来继承不能创造实例
var Animal = /** @class */ (function () {
    function Animal(name, age) {
        this.name = name;
        this.age = age;
    }
    Animal.prototype.sayHello = function () {
        console.log("I am Class Animal.");
    };
    return Animal;
}());
var Cat = /** @class */ (function (_super) {
    __extends(Cat, _super);
    // 构造函数
    function Cat(name, age, color) {
        var _this = 
        // 调用基类的构造函数
        _super.call(this, name, age) || this;
        _this.color = color;
        return _this;
    }
    // 函数
    Cat.prototype.run = function () { console.log("".concat(this.name, " is running")); };
    // 函数重写
    Cat.prototype.sayHello = function () { console.log("I am Class Cat."); };
    return Cat;
}(Animal));
var Dog = /** @class */ (function (_super) {
    __extends(Dog, _super);
    function Dog() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Dog.prototype.run = function () { console.log("".concat(this.name, " is running")); };
    Dog.prototype.sayHello = function () { console.log("I am Class Dog."); };
    Dog.prototype.baseSayHello = function () {
        // 使用 super 来访问基类属性和方法
        _super.prototype.sayHello.call(this);
        // 使用 this 来访问当前类
        this.sayHello();
    };
    return Dog;
}(Animal));
var cat = new Cat("mimi", 5, "yellow");
var dog = new Dog("wowo", 3);
cat.sayHello();
dog.sayHello();
dog.baseSayHello();
