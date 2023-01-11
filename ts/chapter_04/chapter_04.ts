// 以 Animal 为抽象类基类，abstract 抽象类只能用来继承不能创造实例
abstract class Animal {
    public name: string;
    public age: number;

    constructor(name: string, age: number) {
        this.name = name;
        this.age = age;
    }

    public sayHello(): void {
        console.log("I am Class Animal.");
    }

    // 抽象方法基类中不定义，交给子类实现
    abstract run(): void;
}

class Cat extends Animal {
    public color: string;
    // 构造函数
    constructor(name: string, age: number, color: string) {
        // 调用基类的构造函数
        super(name, age);
        this.color = color;
    }
    // 函数
    public run(): void { console.log(`${this.name} is running`); }
    // 函数重写
    public sayHello(): void { console.log("I am Class Cat."); }
}

class Dog extends Animal {
    public run(): void { console.log(`${this.name} is running`); }
    public sayHello(): void { console.log("I am Class Dog."); }
    public baseSayHello(): void {
        // 使用 super 来访问基类属性和方法
        super.sayHello();
        // 使用 this 来访问当前类
        this.sayHello();
    }
}


let cat = new Cat("mimi", 5, "yellow");
let dog = new Dog("wowo", 3);
cat.sayHello();
dog.sayHello();
dog.baseSayHello();