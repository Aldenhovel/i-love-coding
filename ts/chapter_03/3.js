var Gender;
(function (Gender) {
    Gender[Gender["male"] = 0] = "male";
    Gender[Gender["female"] = 1] = "female";
})(Gender || (Gender = {}));
var Person = /** @class */ (function () {
    function Person(name, age, gender) {
        if (gender === void 0) { gender = Gender.male; }
        // 构造函数
        this.orgname = name;
        this.name = name;
        this.age = age;
        this.gender = gender;
    }
    Person.prototype.show = function () {
        // 类函数
        console.log("*******************************");
        console.log("name: " + this.name);
        console.log("age: " + this.age);
        console.log("gender: " + this.gender);
        console.log("*******************************");
    };
    Person.prototype.setAge = function (age) {
        this.age = age;
    };
    Person.getClassName = function () {
        // 静态类方法
        return this.classname;
    };
    Object.defineProperty(Person.prototype, "qq", {
        // get set 函数可以更好地隔离 private 属性
        get: function () {
            return this._qq;
        },
        set: function (qq) {
            this._qq = qq;
        },
        enumerable: false,
        configurable: true
    });
    // 静态
    Person.classname = "person";
    return Person;
}());
var LiMing = new Person("LiMing", undefined, Gender.female);
LiMing.show();
LiMing.setAge(19);
LiMing.show();
console.log(Person.classname);
console.log(Person.getClassName());
LiMing.qq = "178";
console.log(LiMing.qq);
