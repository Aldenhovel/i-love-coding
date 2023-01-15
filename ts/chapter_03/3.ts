enum Gender {
    male,
    female,
}

class Person {
    // 类属性
    public name: string;
    public age: number;
    public gender: Gender;
    private _qq: string;
    // 只读
    readonly orgname:string;
    // 静态
    static classname: string = "person";

    constructor(name: string, age?: number | any, gender: Gender = Gender.male) {
        // 构造函数
        this.orgname = name;
        this.name = name;
        this.age = age;
        this.gender = gender;
    }
    public show(): void {
        // 类函数
        console.log("*******************************");
        console.log("name: " + this.name);
        console.log("age: " + this.age);
        console.log("gender: " + this.gender);
        console.log("*******************************");
    }
    public setAge(age: number): void {
        this.age = age;
    }
    static getClassName(): string {
        // 静态类方法
        return this.classname;
    }

    // get set 函数可以更好地隔离 private 属性
    get qq(): string {
        return this._qq;
    }
    set qq(qq:string) {
        this._qq = qq;
    }
}


let LiMing = new Person("LiMing", undefined, Gender.female);
LiMing.show();
LiMing.setAge(19);
LiMing.show();
console.log(Person.classname);
console.log(Person.getClassName());
LiMing.qq = "178";
console.log(LiMing.qq);