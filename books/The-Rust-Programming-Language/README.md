- [Programming in Rust](#programming-in-rust)
  - [Chapter 1-2 Introduction to Rust 🦀](#chapter-1-2-introduction-to-rust-)
    - [Rustup, Rustc and Cargo - package manager](#rustup-rustc-and-cargo---package-manager)
  - [Chapter 3 - Common Programming Concepts](#chapter-3---common-programming-concepts)
    - [Chapter 3.1: Variables and Mutability](#chapter-31-variables-and-mutability)
    - [Chapter 3.2: Data Types in Rust](#chapter-32-data-types-in-rust)
    - [Chapter 3.3 - Functions in Rust](#chapter-33---functions-in-rust)
    - [Chapter 3.5 Control Flow](#chapter-35-control-flow)
  - [Chapter 4 Understanding ownerships](#chapter-4-understanding-ownerships)
    - [Chapter 4.1 What is ownerships ?](#chapter-41-what-is-ownerships-)
    - [Chapter 4.2 References and Borrowing](#chapter-42-references-and-borrowing)
    - [Chapter 4.3 The Slice Type](#chapter-43-the-slice-type)
  - [Chapter 5. Using Struct to Structure Related Data](#chapter-5-using-struct-to-structure-related-data)
    - [Chapter 5.1 Defining and Instantiating structs](#chapter-51-defining-and-instantiating-structs)
    - [Chapter 5.2 An example program using structs](#chapter-52-an-example-program-using-structs)
    - [Chapter 5.3 Method syntax](#chapter-53-method-syntax)
  - [Chapter 6 - Enums and Pattern Matching](#chapter-6---enums-and-pattern-matching)
    - [Chapter 6.1 Defining an Enum](#chapter-61-defining-an-enum)
    - [Chapter 6.2 - The match control flow construct](#chapter-62---the-match-control-flow-construct)
    - [Chapter 6.3 - Concise Control flow with `if let`](#chapter-63---concise-control-flow-with-if-let)
  - [Chapter 7 - Managing Growing Projects with Packages, Crates, and Modules](#chapter-7---managing-growing-projects-with-packages-crates-and-modules)
  - [Chapter 8 Common Collections](#chapter-8-common-collections)
  - [Chapter 9 Error Handling](#chapter-9-error-handling)
  - [Chapter 10 Generic Types, Traits, and Lifetime](#chapter-10-generic-types-traits-and-lifetime)

# Programming in Rust

Short notes on Rust - System Programming Language 

## Chapter 1-2 Introduction to Rust 🦀

### Rustup, Rustc and Cargo - package manager

- `Rustup` maintains all the packages
- Every rust program must contains a function called as `main`
- `rustc` takes Rust file as input and generate a binary executable
- ***Cargo*** is rust package manager
- To create a new project using cargo
    
    ```bash
    $ cargo new <project-name>
    ```
    
- Build the project and create the executables
    
    ```bash
    $ cargo build 
    ```
    
- Run the executables
    
    ```bash
    $ cargo run 
    ```
    
- Doesn't produce any executable but check whether code compile or not
    
    ```bash
    $ cargo check
    ```
    
- To update the crates
    
    ```bash
    $ cargo update
    ```
    
- **Input/Output** library into scope
    - `use std::io` - I/O library comes from standard scope
    - `io` module provide us several functions like `stdin()`
- `println!()` is a macro which prints string to the screen
- **Storing values with a variable**
    - In rust variable are ***immutable*** by default, meaning once value
    is assigned, the value won't change
    - To have a ***mutable*** variable you have to prefix that with `mut`
- **String**
    - `String::new`, a function that returns a new instance of a String
    String is a string type provided by standard library that is growable
    - The syntax `a::b`
        - This syntax represent that `b` is associated with `a`
        - Ex. `let mut guess = String::new();`
        - `new` function creates a empty initialization of the type
- **What are associated functions ?**
    - A type of function that is implemented on a type, in the above
    case it was `String`
- **Receiving User Input**
    - `io::stdin().read_line(&mut guess)`
    - From `io` module we are calling `stdin()` function, this will return you a
    `std::io::Stdin` handle, over this handle you will call the method
    `read_line`. We are also passing `&mut guess` as an argument to the
    `read_line`
    - String argument need to be mutable so that method can change this
    - `&` means reference, which means we are not passing any copy of data
    instead we are passing the reference
- Handling potential failure with a **Result Type**
    - `read_line` returns a `Result` value.
    - Result is an enum (often called enumeration) which is a type that can be in one of multiple possible states
    
    <aside>
    📌 We call each of these **states** as **variant**
    
    </aside>
    
    - The purpose of **Result** is to encode the error-handling information
    - Result's value is `Ok` or `Err`
        - `Ok` represents the operation was successful
        - `Err` contains the information about how and why the operations
        failed
    - Value of Results type have method defined over them
    - Like except method you can call over a result object
    - If *Results is an Err value*, expect will cause program to terminate immediately
    - If the Results is Ok then except with return the value that ok is holding
    - If you don't call except, the program will compile, but you'll get a warning 🦀
- Using crates for more functionality
    
    <aside>
    📌 Crate is a collection of Rust source code files
    
    </aside>
    
    - We are building binary crates, which is an executable
    - The `rand` crate is a library crate, which create code that is intended to use
    - In ***cargo.toml*** file you can mention all the dependencies
        
        ```bash
        [dependencies]
        rand = "0.8.5"
        ```
        
    - Cargo understand the semantic versioning
    - This is called an external dependencies
    - When we include an external dependency, Cargo fetches the latest version of everything that dependency need from the registry, which is a copy of Crates.io
    - People in Rust ecosystem post the open source Rust projects for others to use

**Cargo is smart!** 🧠

- It avoid to compile code again if there are no changes, it simply exits

**Cargo reproduces builds**

- Cargo has mechanism that ensures you can rebuild the same artifact every time you or anyone else build your code

**Immutable types in Rust** 

- We need to prefix the types with `mut` in order to make them `mut`

## Chapter 3 - Common Programming Concepts

### Chapter 3.1: Variables and Mutability

- Variables in Rust are immutable by default. Once you bind a value to a name,
you can't change the value
- How immutable are different than constants ?
    - `let x`, x is a variable and it can be `mut` and immutable
    - `const x`, can't be `mut`, it is by nature immutable
    
    <aside>
    ✅ Also, constants may be set only to a constant expression, not the results of a value that could only be computed at run time, more or less like natural constants
    
    </aside>
    
    <aside>
    📌 Naming convention for constants: ALL CAPITAL
    
    </aside>
    
    - constants are valid for the entire time a program runs, within the scope
    they are declared
- **Shadowing**
    - If you declare same variable more than one, the later will take up the
    or shadow the earlier one.
    - Shadowing is different from making a variable `mut` because we'll get a
    compile-time error. We can't assign there again, where here we are saying
    we are going to have a complete fresh variable
        
        ```rust
        // Below two lines is ok in rust
        let spaces = " ";
        let spaces = spaces.len(); 
        // Below two lines are NOT ok in rust
        let mut spaces = " ";
        spaces = spaces.len(); // Type is changed, which is not allowed
        
        ```
        

### Chapter 3.2: Data Types in Rust

- Every value in rust belongs to some datatype
- Rust is statically typed language, types are fixed during compiling or types must be known during compile time
- The compiler usually infer the type from the value which we want to use
- But there will be time when compiler will not able to do so, in that case you have to explicitly add type annotation
- **Scalar Types**
    - There are typically 4 type of scaler in rust
    - Integer, Floating point, boolean, characters
    - Integer further classified into subclasses
        - `(8, 16, 32, 64, 128)` bit signed and unsigned
        - `i8` represent signed, `u8`, represents unsigned
        - If only positive then represented using un sign (default assumption)
        - Sign variants can store negative values ranging from $-2^{n - 1}\ to\ 2^{n - 1}-1$  inclusive
        - These are stored in 2's complement form
        - Additional to those we also have arch(which says architecture dependent)
            - If you system is **x-bit** then it will take **x-bit** for storing that number
    - Integer Literals are also there
        - `_` for visual separator ex. 100_00_000
        - `0x` for Hex
        - `0o` for octal
        - `0b` for binary
        - `b'A'` for bytes
    - Floating point types
        - `f32` and `f64`
    - Boolean types
        - `let f: bool = true or false;`
    - Char are also primitive type in rust
        - Rust allows characters to be of 4 bytes and thus allow ASCII
- **Compound Types**
    - Tuple (grouping numbers together)
    `let tup: (i32, f64, u8) = (500, 6.4, 1);`
        - Elements of tuple can be accessed using `.`
    - Array Type
        - Every element of array must of same type, unlike in tuple where multiple types are allowed
            
            ```rust
            let a: [i32; 5] = [1, 2, 3, 4, 5];
            // An array a of type i32 and 5 elements
            ```
            
        - To access elements of array it is simple `a[i]`
        - There can some runtime error if an element of array is accessed for which index is *out-of-range*

### Chapter 3.3 - Functions in Rust

- Functions names are ***snake case***
- `fn` keyword
- Parameters - A functions has parameters, and the concrete values that you provide to those are called as arguments
- In function signature, you must declare the type of each variable. This is strict in rust
- **Statement vs Expressions**
    - Statement doesn't return anything, for example `let x = 5;`
    - That's why we can't do `let x = (let y = 6);`
    - Expressions are evaluated to have a resultant values
    - This is different from other language and thus statement in rust returns nothing
    - So `x = y = 6;` is complete invalid in rust
    - Note expression don't include ending semicolons. If you have semicolons then it is no more expression, it become statement
    - Return value in functions
        
        ```rust
        fn function_name(parameter: parameter_type) -> return_type
        ```
        

### Chapter 3.5 Control Flow

- **if** condition "must" take an expression which evaluates to a boolean value unlike programming language like C or CPP where if a works even when a is integer, the same thing is not allowed in rust
    - You can have if else like other programming language
    - The results of both if and else arm must be of same types
        
        ```rust
        let number = if condition { 5 } else { "six" };
        ```
        
- Repetition with loops
    - `loop {}`, `break` and `continue` statements
    - Returning value from the loops
        - `break value_expression;`
    - Examples of loop
        
        ```rust
        let result = loop {
        	counter += 1;
        	if counter == 10 {
        		break counter * 2;
        	}
        };
        ```
        
    - Loop labels to uniquely identify
        - See code for more, it's like naming to loops and then to break and
        continue you can tell to which you want to apply this
    - For loops are the most common kind of loops

## Chapter 4 Understanding ownerships

### Chapter 4.1 What is ownerships ?

- This will help rust to provide memory safe guarantees without needing a garbage collector
- Three wheels of memory management
    - Write garbage collectors
    - Let the programmer do the work - **allocate** and **free** memory
    - Rust way of memory management - system of ownerships
- **What is ownerships ?**
    - Ownerships in rust are checking during compile time itself, if they are violated, the code will not get compiled
    - Ownerships has no impact on the runtime of your code (all are compile time rules)
    - All data stored on the stack must have a known, fixed size.
    - Data with an unknown size at compile time or a size that might change must be stored on the heap instead.
    - Keeping track of data on heap, minimising the amount of duplicate data on the heap, and cleaning up unused data on the heap so you don't run out of space are all problems that ownerships addresses.
- Ownership Rules
    - Each value in Rust has an owner
    
    <aside>
    📌 There can be one owner at a time
    
    </aside>
    
    - When owner goes out of scope the value get dropped.
    
    ```rust
    { 
    	// s is not valid here, it's not declared
    	s = "hello";
    	// s is valid from this point forward
    } 
    // this scope is over now, thus s got dropped or no more valid
    ```
    
- To understand the concept of ownership we will look at String in rust
    
    ```rust
    let s = String::from("hello");
    // :: suggest the namespaces under which "from" function is used, it comes
    // under String
    
    let mut s = String::from("hello");
    s.push_str(", world!");
    // We can push string or we can mutate them, but we can't mutate string 
    // literals
    ```
    
    - The main difference between **String** and **String literals** is the way they are stored.
    - Since the size of string literal is known at the time of compile time, so they are hardcoded into the code into the final executable.
    - That's why they are fast, but they come up with the drawback that they are **immutable** then.
    - But with the String type we are allocating memory on the heap, thus even unknown during the compile time is ok
        - The memory is allocated by the allocator and thus we also need to figure out a way so that we can return it back once we are done with the usage.
        - If GC takes this responsibility then we have two risk, if it free soon, then we will have invalid memory references, but if delay it too, then we are risk under wasting the resource.
    - Rust uses a special function "drop" and it put it at the end of curly bracket, when variable goes out of the scope, Rust call this special function
    - Move and copy
        
        ```rust
        let x = 5;
        let y = x;
        ```
        
    - Here in the above **"5 is bind to x"**, and when we write `y = x`, we are just creating a copy on the stack.
    - But what should happen if
        
        ```rust
        let s1 = String::from("hello");
        let s2 = s1;
        ```
        
        - Consider the information associated with String `s1` - (ptr, len, capacity)
        - **ptr** points to (`index: [0, 1, 2, 3, 4]`, `value: ['h', 'e', 'l', 'l', 'o']`) The content ptr, len and capacity is stored on stack and whatever actual string is which is pointed by ptr, is stored on heap
    - So when we are saying `s2 = s1`, it essentially means that `s2` points to the same heap but rest is copied, so the things which are on stack are copied for `s2`, but heap is still in shared
    - But now whose **duty** is to **free the memory** ❓
        - If `s1` and `s2` both try to free then it will be **double free** error.
        - When we say `let s2 = s1`, `s1` remain no more valid after this line and rust
        need not to clear any thing once `s1` goes out of scope
    - Consider the code snippet
        
        ```rust
        let s1 = String::from("hello");
        let s2 = s1;
        println!("{}, world!", s1);
        ```
        
    
    <aside>
    🦀 Rust during compile time will generate the error saying that `s1` is already moved to `s2`
    
    </aside>
    
    - In other language this might sounds like shallow copy, but instead this is completely different from that, instead saying a shallow copy exists, rust completely invalidate the s1. So it's called as **move**.
    
    <aside>
    📌 Rust will never deep copied your data, instead you have to do it explicitly, saying `.clone()` on object
    
    </aside>
    
    - Rust has a special **annotation** called **`Copy` trait** that we can place on the traits that are stored on stack, as integers are.
    - If a type implements the `Copy` trait, variable that use it do not move, but rather are trivially copied, making them still valid after copy
    
    <aside>
    🔒 Rust won't let us annotate a type with `Copy` trait if it has implemented `Drop` trait
    
    </aside>
    
- If you pass a value which implement Drop trait to a function, its ownership move permanent to that function, and now the point where you called, after that point it remains no more valid.
- So to get the variable you have to return that back from the function, but then that will become too much annoying 😧, right ?
- So Rust for that case provides you with something called as **references** (discussed in section 4.3)

### Chapter 4.2 References and Borrowing

- So instead passing a variable which is on heap to a function, we will pass the reference to that variable to the function, in that case the ownership will not be moved but instead a reference will get passed.
- Since the value is not owned and thus it will also not get drop once the variable will goes out of scope.
- The action of creating references is called **Borrowing**
- So What if try to mutate the borrowed variables ?
    - You can changes, just as variables are immutable by default, so are the references
- So now what ? **How to changes if they are not immutable ?** 🤷‍♂️
    - But who said that they can't be mutable ?
        - Yes, you can make them mutable, but once you have mutable reference, there is no scope for having any other variable which is also a reference to that same variable.
        - Any sort of reference, whether it is **mutable** or **immutable** (means no reader and writer to that variable)
    - So, this allow us to mutate but in very constraint manner or better to say in control manner.
    - This will block all the **data races** that can be there
    - A data race is similar to the race condition and happen when these three behavior will occurs
        - Two or more pointers access the same data at the same time.
        - At least one of the pointer being used to write to the data.
        - There is no mechanism being used to *synchronise* access to the data.
    - Data races causes indeterministic behavior and they are hard to track
- **Dangling pointers**
    - A pointer that references a location is memory that may have been given to someone else, by freeing that memory, but preserving the pointer.
    - The compiler in rust guarantees that references will never be dangling reference
    - If you have reference to some data, the compiler will ensure that the data will not go out of scope before the reference to the data goes.

<aside>
🦀 **Rust Rules**

1. At any given time, you can have either **one mutable reference** or **any number
of immutable references**
2. References must always be valid
</aside>

### Chapter 4.3 The Slice Type

- Slice will let you reference a continuous sequence of elements in a collection rather than the whole collection.
- Since it is a reference it doesn't have ownership, so slices are `immutable`
- `&str` type and it can also accept `&String` type
- Since it is a immutable reference that means that there can't exist any mutable reference, thus string will not get modified once you have this hold in your hands.
- Why needed slice type ?
    - Because say if you find some character at some index, and later someone remove the string completely, but you still have index and if you will try to access that location, your code will break during runtime, but we don't want that.
- Let’s think why the above is happening on the first hand ?
    - This was happening because there was not **strict relation** between both index and string
    - But as soon as you have slice - they are binding together now through immutable reference to slices of string, this will restrict any one to change.
    - Or we should read this other way, since we don't want our string to changes, once some variable is holding some index to that string for some characters, then only way we can do that is that produce a immutable reference to that string and now compiler will make sure that there is no one who can change the string
- When you create a slice, essentially you create a pointer on the stack, which stores information related to the **(ptr, len)**, where **len** is the length of the slice and **ptr** points to the location where this slice points to.
- This is applicable to the arrays too
    
    ```rust
    fn take_slices(s: &str) -> &str {
    		...
    }
    ```
    
- The above code takes a immutable reference to slice as input and also returns a immutable reference to the slice as output
- Example -
    
    ```rust
    let s = String::from("hello");
    let slice = &s[..3];
    ```
    

<aside>
🦀 All the concepts we have discussed above ensures memory safety in the Rust program at the compile time and thus makes Rust a powerful language
1. **Ownership**
2. **Borrow**
3. **Slice**

</aside>

## Chapter 5. Using Struct to Structure Related Data

### Chapter 5.1 Defining and Instantiating structs

- Structs are more general type of tuple, where both allow you to hold the different values, but structs also allow to name those.
- Keyword `struct` is used to defined structures
    
    ```rust
    struct User {
    	active: bool,
    	username: String,
    	email: String,
    	sign_in_count: u64
    }
    
    // Create an instance of the struct by specifying concrete values
    let user = User {
    	active: true,
    	username: String::from("souraavv");
    	email: String::from("mcs212154@cse.iitd.ac.in");
    	sign_in_count: 5000,
    };
    
    // To get a specific value from the string - use the dot notation
    user1.email // gives you the email address
    ```
    
- To get a specific value from the struct, we use dot notation ex. to access the email address, we can use `user1.email`. If the instance is mutable we can also change the value
- Note entire instance need to be mutable, Rust don't allow to marks specific set mutable and rest immutable.
- If parameter name and struct field names are same, then you don't required to
use key:value pair while building the instance, you can directly use the value
only.
- You can also use the properties of other instance and can modify few
    
    ```rust
    fn main() {
    		let user2 = User {
    				active: user1.active,
    				username: user1.username,
    				email: String::from("sourav@gmail.com");
    				sign_in_count: user1.sign_in_count;
    		};
    }
    ```
    
    <aside>
    📌 Note when those object which apply **Copy trait** are the only one which get copied on stack, rest all other get a reference
    
    </aside>
    
- Tuple structs **without name fields**. These are useful when you want to assign the tuple a name, but not each key which it contains
    
    ```rust
    struct Color(i32, i32, i32);
    struct Point(i32, i32, i32);
    
    fn main() {
    	let green = Color(0, 0, 1);
    	let origin = Point(0, 0, 0);
    }
    ```
    
- The above syntax become much more readable
- Unit-Like Structs without any fields, these behaves similar to the `()`, later we find the use case in Chapter 10 of traits
- For now we are using `String` type in `struct`, can we also have `&str` ? or reference
    - Yes, we can have but for that we need to associate the **lifetime parameter**
- **Lifetime** ensures that the data referenced by a struct is valid for as long as the struct is.

### Chapter 5.2 An example program using structs

- Note `println!()` takes the reference, where as `dbg!` macro takes the ownership
- With struct to print `use #[derive(Debug)]`
- `Debug` is a **trait**, rust provides a number of traits with the derive attribute
- Trait's are basically the inherited properties from some parent P.
- If parent knows a function or implemented something, child can owns the knowledge without implemented it, or it can change if want.

### Chapter 5.3 Method syntax

- Methods are similar to the functions, we declare them with the fn keyword and a
name, they can have parameter and return values
- Methods are defined in the context of struct, unlike functions which have no such
context.
- For more detail find code *@../chapter5/src/main.rs*
    
    ```rust
    #[derive(Debug)]
    struct Vector {
    	x: i32,
    	y: i32,
    }
    
    let v1: Vector = Vector {
    	x: -1,
    	y: 1
    };
    
    let v2: Vector = Vector {
    	x: 3,
    	y: 2
    };
    
    impl Vector {
    	fn add(&self, other: &Vector) -> Vector {
    			let res: Vector = Vector {
    					x: self.x + other.x,
    					y: self.y + other.y
    			};
    			res
    	}
    	fn multiply(self: &Self, other: &Vector) -> Vector {
    			let res: Vector = Vector {
    					x: self.x * other.x;
    					y: self.y * other.y;
    			}
    			res
    	}
    }
    
    let v3: Vector = v1.add(&v2);
    ```
    
- `&self`, is a short hand for `self: &Self`
- `impl` is a block - `self` is an alias for the type that the `impl` block is for.
- Method can borrow self or take the ownership
    
    <aside>
    🦀 `&mut self` we can use if we want to make changes to the self, but if don't then by default all in rust is immutable
    
    </aside>
    
- **Automatic referencing and dereferencing**
    - In C and CPP we have seen that if object is a pointer, and if we want to use to call something then we need to use either `object->something()` or `(*object).something()`.
    - In the later case we first dereferencing and then accessing
    - There is no equivalent of `->` in Rust. Instead rust by its design doesn't require this thing.
    - Rust automatically adds `&`, `&mut`, `*` so that object matches the signature of the method (i.e self)
    - Ex. `p1.distance(&p2);` is same as `(&p1).distance(&p2);`
    - But we can see the first one is cleaner and that what we all need to do while using rust
    - This is possible because we have clear behavior or receiver i.e self in the method.
    - Rust can figure whether method is using `&self`, or `&mut self`
    
    <aside>
    🦀 Also one beautiful thing if you notice is that rust by-default made the borrowing implicit for methods i.e `&self` and thus making ownership ergonomic in practice.
    
    </aside>
    
- All functions within the `impl` block are called as ***associated functions*** because they're associated with the type named after the `impl`.
- Methods are subset of associated functions
- An associated functions doesn't require necessary to have self as first argument
- We have already seen these kind of functions ex. `String::from()` function that is defined on type `String`. You are not creating any object first and then called from, it can be directly invoked.
- From the above you might get the intuition where we can use these ? We can use these type of functions as constructors that will returns a new instance of the struct.
    
    ```rust
    impl Rectange {
    	fn square (size: u32) -> Self {
    		Self {
    			width: size,
    			height: size,
    		}
    	}
    }
    ```
    
- The `Self` keyword here is an alias for the type name that is present just after the impl keyword, which in this case is Rectangle
- To call any associated function, we use `::` syntax with the struct name; `let sq = Rectangle::square(3);`
- We can have multiple `impl` blocks, although they are unnecessary if methods are implemented for a same type, but still that is a valid syntax
- **Overall summary**
    - Struct allows you to create custom types that are meaningful for your domain
    - By using structs, you can keep associated piece of information together and
    also a name get associated with that
    - `impl` blocks allow to have associated functions with your types
- Note struct are not the only way to have custom types in rust, we can also have enum to do so

## Chapter 6 - Enums and Pattern Matching

- Enumerations are the possible set of values which can be take by some variable.
- Say if a variable can take 5 different set of values in it's entire lifetime
- Instead just tagging them as some random constant integers/character/string, it's better to capture all these types under some name.
- And now that type is a custom type for which range is defined by the user, rather than some specified range, like integer, characters, ...
- This can make your code looks more clean and readable
- We will also look at some particular enum like OPTION
- Also we see if let construct idiom available to handle enums in your code

### Chapter 6.1 Defining an Enum

```rust
#[derive(Debug)]
enum IpAddrKind {
		V4,
		V6,
}

#[derive(Debug)]
struct IpAddr {
		kind: IpAddrKind,
		address: String,
}

let home = IpAddr {
		kind: IpAddrKind::v4,
		address: String::from("127.0.0.1");
};

let loopback = IpAddr {
		kind: IpAddrKind::v6,
		address: String::from("::1")
};

println!("{:?}", home);
println!("{:?}", loopback);

// Instead of above we have better way to do in Rust

```

But enum is much more than the above

```rust
#[derive(Debug)]
enum IpAddr {
		v4(String),
		v6(String)
}
let home: IpAddr = IpAddr::v4(String::from("127.0.0.1"));
let loopback: IpAddr = IpAddr::v6(String::from("::1"));
println!("The ip of home = {:?} and loopback = {:?}", home, loopback);
```

- Enum are well able to capture the data too. Each variant of enum now almost kind of a type itself.
- A sample enum, instead using four struct and then show all these types, enum are well able to capture all these in a single go.
- That will create mess, you may design multiple function which takes those type as input, here all are of Message types
    
    ```rust
    enum Message {
    		Quit,
    		Move {x: i32, y: i32},
    		Write(String),
    		ChangeColor(i32, i32, i32),
    }
    ```
    
- Also similar to the struct, enum can also use `impl` block
    
    ```rust
    impl Message {
    		fn call(&self) {
    				println!("Writing the message...");
    		}
    }
    let msg = Message::Write(String::from("hello world!"));
    msg.call();
    ```
    

<aside>
📌 Let's also look at one of the standard **enum** called as `OPTION` and it's advantage over null values

</aside>

- **Option** is used to capture the value(something) or it could be nothing
- Say if you are accessing a list and if list is non-empty then you will get the element, but in case if it is empty, then you will get nothing.
- This type of capturing allow compiler to check you code in a better way. Like whether you are looking for all the cases in your code or not ?

<aside>
🦀 There is no null in rust unlike other language, which mean nothing

</aside>

- The problem with null value is that if you try to use it as non-null value then it can cause several issue

<aside>
💰 The creator of **null** Tony Hoare said **"Null References: The Billion Dollar Mistake"**

</aside>

- However, the concept of null is imp as it is trying to express that the value is currently invalid or absent due to some reason
- **The problem is not with the null concept, but the way it is implemented**
    
    ```rust
    enum Option<T> {
    		None,
    		Some(T),
    }
    ```
    
- It is default included in prelude, you don't need to include it in scope explicitly
    
    ```rust
    let some_number = Some(5);
    let some_char = Some('e');
    let absent_number: Option<i32> = None;
    ```
    
- For first two rust can annotate them based on the value on the r.h.s of `=`
- But for the third one i.e `absent_number`, Rust can't do that on it's own and thus required to annotate by the user
- But can we **add** `i8` and `Option<i8>` ? No, since rust is identifying those as separate variable, you can't.
- So, first you have to convert `Option<i8>` to `i8` or `Option<T>` to `T`
- Generally, this helps eliminating the issue of something being null, when it is assumed to be not, since you have to convert it first and there you can detect the bug itself.
- There are several method that enum `Option<T>` has implemented, to extract out `T` from
`Some(T)`
- Match expression is a control flow that provide
- Match will run the code based on the variant of enum which it has currently

### Chapter 6.2 - The match control flow construct

- Rust has an extremely powerful control flow construct called `match` that allow you to compare a value against a series of pattern
- The power of `match` comes from the expressiveness of the pattern and the fact that the compiler confirms that **all possible cases** are handled
- This is also a lot different from `if`, in case of if we evaluates the boolean conditions but here we can match with types too. Now consider the combination of `enum` with `match`
- Each match has it arms followed by `=>`
- The code associated with each **arm** is an **expression**
- If code is short, i.e one single expression then there is no requirement of of `{}`
- Matches are always exhaustive - Look at the below example
    
    ```rust
    fn plus_one(x: Option<i32>) -> Option<i32> {
    		match x {
    				Some(i) => Some(i + 1),
    		}
    }
    ```
    
- The above code will raise issue since there is no matching for the `None`
- In case if you want you can have a placeholder "other" which matches everything
    
    ```rust
    let dice_roll = 9;
    match dice_roll {
    		3 => add_fancy_hat(),
    		7 => remove_fancy_hat(),
    		other => move_player(other),
    }
    fn ad_fancy_hat() {}
    fn remove_fancy_hat() {}
    fn move_player(num_spaces: u8) {}
    ```
    
- In case if the value doesn't matter to use then instead of writing `other` we can simply put a underscore `_`
- There is no binding in case of `_`, where as in all other case the value is bind.
    
    ```rust
    let dice_roll = 9;
    match dice_roll {
    		3 => add_fancy_hat(),
    		7 => remove_fancy_hat(),
    		_ => (),
    }
    fn add_fancy_hat() {}
    fn remove_fancy_hat() {}
    ```
    
- Also, you can tell that don't execute anything for a specific arm if you want.

### Chapter 6.3 - Concise Control flow with `if let`

- In the last example of chapter 6.2, it might be annoying to handle _ => () because here you don't want to do anything to the rest of cases. In case if you want then it is ok.
- So, we have combination of `if let`
    
    ```rust
    let config_max = Some(3u8);
    if let Some(max) = config_max {
    		println!("The max value of configuration is {max}");
    }
    ```
    
- In this case `max` bind to the value store by `config_max`
- However, you **loose exhaustive checking** in case of `if let`, in case of matching you are forced to do so.
- In other words, `if let` is a **syntax sugar** 🍬 for a match that runs code when the value matches one pattern and then ignores all other values
- We can also add `else` to do something with the rest of the cases

## Chapter 7 - Managing Growing Projects with Packages, Crates, and Modules

- Most of the programs we have written till are limited to single module in one file
- A **package** can contain multiple **binary crates** and optionally **one library crate**
- Cargo provides **Cargo Workspaces** section (In future chapter 14)
- **Module system**
    1. **Packages**: A Cargo feature that let you build, and share crates
    2. **Crate**: A tree of modules that produces a library or executable
    3. **Modules and use**: Let you control the organization, scope, and privacy of paths
    4. **Paths**: A way of naming an item, such as struct, function, or module
    
    ### Chapter 7.1 Packages and Crates
    
    - Crates comes in two format
        1. **Binary crate** : which contains main function and they are compiled to generate executable
        2. **Library crate** : Don't have main function and not compiled, ex. Random crate
    - Crate is the smallest amount of code that the Rust compiler considers at a time
    - The crate root is a source file that the Rust compiler start from and makes up the root module of your crate
    - A package is bundle of one or more crates that provides a set of functionality.
    - A package contains *cargo.toml* file that describe how to build those crates
    - *Cargo* is a package that contains the binary crate for the command line tool you've using to build your code
    - The *Cargo* package also contains a library crate that binary crate depends on
    - A package can contains as many as binary crates you want, but at most only one
    crate
    - A package must contains at least one crate
    - When you write cargo new my-project, then *cargo* creates a project directory there's a *Cargo.toml* file, giving us a package. There's also a *src* directory that contains [main.rs](http://main.rs/) and cargo set up that as the root for rustc to generate executable
    - If *src/lib.rs*, then that is identified as the library crate
    - By default your package only contains a binary crate i.e *src/main.rs*, you can optionally add at most one library crate
    - A package can have multiple binary crates by placing file in the *src/bin* directory: each file will be a separate binary crate
    
    ### Chapter 7.2 Defining Modules to Control Scope and Privacy
    
    - Modules and paths that allow you to name items; the use keyword that brings a path to the scope; and the pub keyword to make items public
    - Module Cheat Sheet:
        1. Start from the crate root: When compiling a crate the compiler first looks in the crate root file (usually *src/lib.rs* for a library crate or *src/main.rs* )
        2. Declaring modules : In crate root file, you can declare new modules; you can declare a *garden* module with mod garden. The compiler will look for the module code in these places:
            - Inline, with curly brackets
            - In the file *src/garden.rs*
            - In the file *src/garden/mod.rs*
        3. Declaring Submodules
        - In any other file than the crate root, you can declare Submodules.
        - For example you might declare mod vegetables; in *src/garden.rs*.
        - The compiler will look for submodule's code within the directory named for the parent module in these places
            - Inline
            - In the file *src/garden/vegetables.rs*
            - In the file *src/garden/vegetables/mod.rs*
        1. **Path to code in modules**
        Once a module is part of your crate (i.e file), you can refer to the code in that module from anywhere else in that same crate. 
        2. For example Asparagus type in the garden vegetables module would be found at
            
            ```rust
             crate::garden::vegetables::Asparagus
            ```
            
        3. **Public vs Private**
            - Code within module is private from it's parent modules by default. To make
            a module public use pub mod instead of mod
            - To make items within a public module public as well, use pub before the declaration
        4. **Use keyword**
            - Create shortcuts in naming to reduce the long paths
        
        **A sample backyard binary crate**
        
        ```bash
        backyard
        ├── Cargo.lock
        ├── Cargo.toml
        └── src
            ├── garden
            │   └── vegetables.rs
            ├── garden.rs
            └── main.rs
        ```
        
    - Grouping Related Code in Modules
    Modules allow to organize codes in the crate (within crate), we have seen the two modules [garden.rs](http://garden.rs/) and a sub-module [vegetables.rs](http://vegetables.rs/)
    - Module also allow the privacy by default, since the code is private by default
    - The reason to call the *src/main.rs* and *src/lib.rs* as the root crate, because rust creates a module named as crate at the root of the crate's module structure, known as module tree
        
        ```bash
        crate
        └── front_of_house
        ├── hosting
        │   ├── add_to_waitlist
        │   └── seat_at_table
        └── serving
        ├── take_order
        ├── serve_order
        └── take_payment
        ```
        
    
    ---
    
    ### Chapter 7.3 Paths for Referring to an Item in the Module tree
    
    - Making a module public doesn't make it's content `public`
    - You can prefer to given absolute path or relative path, absolute is much preferred, since you might need to move you code frequent and thus absolute is best
    - Ex. `crate::front_of_house::hosting::add_to_waitlist();`
    - Sibling requires no pub
        
        ```rust
        mod front_of_house {
            pub mod hosting {
                pub fn add_to_waitlist() {}
            }
        }
        
        pub fn eat_at_restaurant() {
            // Absolute path
            crate::front_of_house::hosting::add_to_waitlist();
        
            // Relative path
            front_of_house::hosting::add_to_waitlist();
        }
        
        ```
        
    - In the above code, `front_of_house` and `eat_at_restaurant` are sibling and thus there is no need to put `public` there. But for the rest like hosting and `add_to_waitlist()` we need to explicitly mark them `public`
    
    ### Chapter 7.4 Bringing Paths Into Scope with the use keyword
    
    ### Chapter 7.5 Separating Modules Into Different Files
    

## Chapter 8 Common Collections

Chapter 8.1 Storing Lists of Values with Vectors

Chapter 8.2 Storing UTF-8 Encoded Text with Strings

Chapter 8.3 Storing Keys with Associated Values in Hash Maps

## Chapter 9 Error Handling

Chapter 9.1 Unrecoverable Errors with panic!

Chapter 9.2 Recoverable Errors with Results

Chapter 9.3 To panic! or Not to panic!

## Chapter 10 Generic Types, Traits, and Lifetime

Chapter 10.1 Generic Data Types

Chapter 10.2 Traits: Defining Shared Behavior

Chapter 10.3 Validating References with Lifetimes

