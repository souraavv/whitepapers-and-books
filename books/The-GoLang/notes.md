
  
## Resources
[Oreilley book - Learning GO by Jon Bodner](https://go.dev/doc/effective_go)
- Total of 16 Chapters : 12 hour of reading 
## Chapter 1

- Go projects are called as modules
- `go mod init <module-name>`
    - Marks the folder as go module 
    - Contains specification of the dependencies
    - Every module has go.mod file (running go mod init create this file)
        - Should not edit the file directly use `go get` or `go mod tidy`

- Build the project
    - `go build -o <name-of-build>` 
    - `./<name-of-build>`
    - Default value for name-of-build is same as module name 

- Automatically fix the whitespaces in your code
    - `go fmt ./...` : Apply command to all the files `.` and all the subdirectories `..`

- `go vet`
    - Detects whether a value exits for each paceholder ?
    - e.g `fmt.Printf("Hello, %s!\n")`
    - ```bash
        got vet ./..
        fmt.Printf format %s reads arg #1, but call has 0 args
      ``` 

## Chapter 2 
- Predeclared Type
    - booleans, integers, floats and strings

- Zero value in Go (to avoid the mistakes of C/C++)
    - Boolean : false
    - String : empty string

- Strings in Go are immutable; 
    - You can reassign the value of a string variable, but you cannot change the value of the string that is assigned to it.

- Literal in Go are untyped 
    ```go

    var x float64 = 10
    var y float64 = 200.3 * 4
    ```

- `var` Vs `:=`
    ```go
    var x int = 10
    var x = 10

    var x int // zero-value 

    var x, y int = 10, 20 
    var x, y = 10, "hello"

    var (
        x int
        y int = 20
        z = 30
        d, e = 40, "hello"
        f, g string 
    )

    ```
    - Go also supports short declaration 
        - When you are within a function, you can use `:=` operatore to replace a `var` declaration that uses type inference 

        ```go
        var x = 10
        x := 10

        var x, y = 10, "hello"
        x, y := 10, "hello"

        - Limitation of `:=` : illegal to use outside the function.

- Tip
    - Don't declare variables at the level of package (most of the time you should only declare inside the methods)
        - Issues ?
            - complicate data flow analysis
            - Subtle bugs (var whose value changes)
            - Difficult to track the changes made to it 
        - In which scenario can use ?
            - immutable variable


- Constants in Go are a way to give names to literals. There is no way in Go to declare that a variable is immutable.
- Another Go requirement is that every declared local variable must be read. It is a compile-time error to declare a local variable and to not read its value.
- The Go compiler won’t stop you from creating unread package-level variables. This is one more reason you should avoid creating package-level variables.
- Unused contants Perhaps surprisingly, the Go compiler allows you to create unread constants with const. This is because constants in Go are calculated at compile time and cannot have any side effects. This makes them easy to eliminate: if a constant isn’t used, it is simply not included in the compiled binary.

- Variables in go used camelCase not snake_case

## Chapter 3 : Composite Types

- Array 
    ```go
    var x = [3]int{10, 20, 30}
    var x = [...]int{10, 20, 30}
    fmt.Println(x == y) // prints true
    ```

- Go only supports one-dimensional arrays, but you can simulate multidimensional arrays:
    ```go
    var x[2][3] int 
    ```

- Can't 
    - read or write past the end of an array
    - negative index
    - If constant literal index, it is a compile-time error
    - out-of-bounds read or write with a variable index compiles but fails at runtime with a panic

- Don't use array unless you know the exact length you need ahead of time
- Limitation with Arrays ?
    - Can't use type conversion to directly convery arrays of different sizes to identical types
    - Can't write a function that works with arrays of any size 
    - Can't assign arrays of different sizes to the same variable
    - Go consider size of the array to be part of the type of the array. Thus [3]int is different type from an array that's declared to be [4]int 
        - That also means you can use an variable to specify the size of an array, because types must be resolved at compile time, not at runtime.
- Why so many restrictions/limited feature in the language ?
    - Main reason array exists in Go is to provide the backing store for slices, which are one of the most useful features of Go.

Slices
> Nil in Go is an identifier that represents the lack of a value for some types (no type)
- A slice is the first type that isn't **comparable**
    ```go
    var x []int
    fmt.Println(x == nil) // prints true

    x := []int{1, 2, 3, 4}
    y := []int{1, 2, 3, 4}
    z := []int{1, 2, 3, 4, 5, 5}
    s := []string{"a", "b", "c"}
    fmt.Println(slices.Equal(x, y)) //print true
    fmt.Println(slices.Equal(x, z)) //print false
    fmt.Println(slices.Equal(x, s))  // does not compile
    ```

    - Zero length slice vs Nil
    ```go
        var data []int
        var x = []int{} // length = 0, capacity = 0
    ```
- append
    ```go
    var x []int
    x = append(x, 10)

    x = append(x, 5, 6, 7)

    ```

- capacity
    - \> than length of the slice
    - If #element in `slice == capacity`, then copy to new location 


[Understanding the Go runtime](https://golab.io/talks/understanding-the-go-runtime)
> Go runtime is compiled into every Go binary
- Go compiler convert code into super fast binary ( by including runtime )

- Go runtime provides
    - Memory allocation
    - Garbage collection 
    - concurrency support
    - Networking
    - Buildin types/functions

- Make in GO
    - create slice with correct initial capacity 

    ```go
     x := make([]int, 5) // len == capacity == 5
     // x[0] .. x[4] = 0

     x := make([]int, 5, 10) // len = 5, capacity = 10 (init)

     x := make([]int, 0, 10) 
     x = append(x, 5, 6, 7, 8)
     // [5, 6, 7, 8] 
    ```

    - If capacity < length && if both are numerical literals or constants
      then compile-time error
      else runtime panic !!

- Emptying a Slice
    - `clear(s)`

- Declaring a slice with defaults
    ```go
     data := []int{2, 4, 6, 8}
    ```

- Slicing Slices 
    ```go
    x := []string {"a", "b", "c", "d"}
    y := x[:2]
    z := x[1:]
    /*
    x : [a b c d]
    y : [a b]
    z : [b c d]
    */
    ```
    - No copying, shared memory 
    - Changing element has side-effects on all slices sharing memory
    - Slicing slices is not recommended

- copy of slices
    ```go
        x := []int{1, 2, 3, 4}
        y := make([]int, 4)
        num := copy(y, x) // destination, source ; returns #element copied
    ```

- copy of array with slices
    ```go
    x := []int{1, 2, 3, 4}
    d := [4]int{5, 6, 7, 8}

    y := make([]int, 2)
    copy(y, d[:])

    /*
     * x : [1, 2, 3, 4]
     * y : [1, 2]
     */
    ```

- Converting slices into arrays
    - This is copying, no memory sharing.
    - Size must be specified at the compile time, thus you can't use `[...]` in a slice to array type conversion
    ```go
    xSlice := []int{1, 2, 3, 4}
    xArray := [4]int(xSlice)

    smallArray := [2]int(xSlice)
    xSlice[0] = 0
    fmt.Println(xSlice)
    fmt.Println(xArray)
    fmt.Println(smallArray)

    /* output : 
     * [10 2 3 4]   
     * [1 2 3 4]
     * [1 2]
     * /
    ```

    - While size of array can be small that the slice, but it can't be larger that the slice size, else you code will panic at runtime

- Strings and Runes and Bytes
    - Go uses sequences of bytes to represent the string
    - These bytes don't have to be in particular character encoding, but several Go library functions (and for-range loop) assumes that a string is composed of UTF-8 encoded code points

    ```go
    var s string = "hello there"
    var b byte = s[5]

    var s2 string = s[4: 7] 
    ```

    ```go
    var s string = "Hello (imagine a sun emoji which is four bytes)"
    var s2 string = s[4:7] // This will not show the emoji, instead [4: 10] will show 
    var s3 string = s[:5]
    var s4 string = s[6:]
    // length of s is not 5(Hello) + 1(space) + 1(emoji), but instead
    // 5 + 1 + 4 = 
    ```
    - String in Go are immutables, thus no side-effects while creating slices
    > There is a problem : UTF-8 ( can be 1-4 bytes ) for non-English letters it can be > 1 bytes, thus we might end up reading  
    - Only use slice on string when you are sure that each character is only taking 1 byte

### Maps
- `map[keyType]valueType`
- `var nilMap map[string]int`
- The zero value for map is `nil`. A `nil` map has a length 0.
- Attempting to read a `nil` map always returns the zero value for the map's value type
- Creating map using literals
    - `totalWins := map[string]int{}`
    - The above is not same as nilMap. It has a length of 0, but you can read and write to a mpa assigned an empty map literal
- Non empty map literal looks like
    ```go
    teams := map[string][]string {
        "abc": []string{"def", "ghij", "klm"},
    }
    ```
- You can use `make` to create a map with a default size
    `ages := make(map[int][]string, 10)

- Reading and Writing a map
    ```go
        totalWins := map[string]int{}
        totalWins["abc"] = 1
        totalWins["def"] = 2
        fmt.Println(totalWins["abc"])
        totalWins["abc"]++
    ```
- The comma ok Idiom
    - How to check if a key is present in map ?
    ```go
    m := map[string]int {
        "hello" : 5,
        "world" : 0,
    }
    v, ok := m["hello"] // value and Ok (boolean) : if true, then key is present, else no
    fmt.Println(v, ok)
- Deleting from Maps / Emptying a map
    ```go
    m := map[string]int {
        "hello", 5,
        "world", 10,
    }
    delete(m, "hello")
    clear(m) // clears the map 
    ```
- Comparing the maps
    ```go
        m := map[string]int{
            "hello": 5,
            "world": 10,
        }
        n := map[string]int{
            "world": 10,
            "hello": 5,
        }
        fmt.Println(maps.Equal(m, n)) // prints true
    ```
- Using Maps as Sets
    - Go doesn't include a set, but you can use map to simulate some of its feature
    ```go
    intSet := map[int]bool{}
    vals := []int{5, 10, 2, 4, ...}
    for _, v := range vals {
        intSet[v] = true
    }
    fmt.Println(len(vals), len(intSet))
    ```

### Struct in Go
```go
type person struct {
    name string
    age int
    pet string
}

var fred person // declare variable on struct

bob := person{} // literal 

// if below format, then provide all the values + order need to same
julia := person {
    "Julia",
    40,
    "cat",
}

// More flexible

beth := person {
    age: 30,
    name: "Beth",
}

fmt.Println(bob.name)
bob.name = "new Name of Bob"

```

- Anonymous structs
    - Helpful in unmarshaling and marshaling data 
    ```go

    pet := struct {
        name string
        kind string
    } {
        name : "Fido",
        kind: "dog",
    }

    ```

## Chapter 4 : Blocks, Shadows, and Control Structure

### Shadowing variable

```go
    func main() {
        x := 10
        if x > 5 {
            fmt.Println(x)
            x := 5
            fmt.Println(x)
        }
        if x > 5 {
            x, y := 5, 20
            fmt.Println(x, y)
        }
        fmt.Println(x)
    }

    // Output
    // 10
    // 5
    // 5 20 
    // 10

```

- Shadowing packages names
```go
func main() {
    x := 10
    fmt.Println(x)
    fmt := "oops"
    fmt.Println(fmt)
}
```

> Weird in Go: int, string, true, false, make, close are not reserved in GO. Go consider these predeclared identifiers and define them in a universal block, which is a block containing all the blocks


```go
    fmt.Println(true)
    true := 10
    fmt.Println(true)
```

### If 
```go
n := rand.Intn(10)
if n == 0 {
    fmt.Println()
} else if n > 5 {

} else {

}
```
- Go feature : Scoping a variable to an `if` statement
- In below code section `n` is only limited to scope of `if/else` and after that it is undefined
- Shadow rules are applicable for the variable `n`
```go
if n := rand.Intn(10); n == 0 {
    fmt.Println()
} else if n > 5 {

}

fmt.Println(n) // out of scope 

```

### for, four ways

- A C style
    ```go
    for i := 0; i < 10; i++ {
        fmt.Println(i)
    }

    i := 0
    for ; i < 10; i++ {
        fmt.Println(i)
    }

    for i := 0; i < 10; {
        fmt.Println(i)
        if i % 2 == 0 {
            i++
        } else {
            i += 2
        }

    }
    ```
- A condition-only `for`
    ```go
    i := 1
    for i < 100 {

    }
    ```
- An infinite `for`
    ```go
    package main
    import "fmt"
    func main() {
        for {
            fmt.Println("hello")
        }
    }
    ```
- `for-range`
    ```go

    envs := []int{2, 4, 5, 8, 10}
    for i, v := range envs {
        fmt.Println(i, v)
    }

    for _, v := range envs {
        ...
    }
    ```

### Iterating over maps

```go
m := map[string]int {
    "a": 1,
    "c": 3,
    "b": 2
}

for i := 0; i < 3; i++ {
    fmt.Println("Loop", i)
    for k, v := range m {
        fmt.Println(k, v)
    }
}
/*
    Loop 0
    c 3
    b 2
    a 1
    Loop 1
    a 1
    c 3
    b 2
    Loop 2
    b 2
    a 1
    c 3
*/
```
- Why different order ?
    - Save from Ddos attack
    - Writing code based on assumption of order is not safe and can break at wierd time
    
### Iterating over strings

```go

samples := []string{"hello", "apple_pi!"} // assume pi as actual pi symbol 

for _, sample := range samples {
    for i, r := range sample {
        fmt.Println(i, r, string(r))
    }
    fmt.Println()
}
```
- Use a `for-range` loop to access the runes in a string in order. 
- The `for-range` value is a copy. Modifying the value of variable will not modify the value in the compound type


### Labelling your for statements
```go
func main() {
    samples := []string{"hello", "world"}

outer:
    for _, sample := range samples {
        for i, r := range sample {
            fmt.Println(i, r, string(r))
            if r == 'l' {
                continue outer <<---
            }
        }
        fmt.Println()
    }
}

// output:  helworl 
```

### Switch in GO

```go
words := []string{"a", "cow", "smile"}
for _, word := range words {
    switch size := len(word); size {
        case 1, 2, 3, 4:
            fmt.Println("shorter")
        case 5:
            wordLen := len(word)
            fmt.Println(word, " is exaclty of lenght", wordLen)
        case 6, 7, 8, 9: // empty case - nothing happens
        default:
            fmt.Println(word, " is a long word!")
    }
}
```

- Check below : break works as == break from the case not the for loop
    ```go
    func main() {
        for i := 0; i < 10; i++ {
            switch i {
            case 0, 2, 4, 6:
                fmt.Println(i, "is even")
            case 3:
                fmt.Println(i, "is divisible by 3 but not 2")
            case 7:
                fmt.Println("exit the loop!")
                break
            default:
                fmt.Println(i, "is boring")
            }
        }
    }
    ```
    ```text
    0 is even
    1 is boring
    2 is even
    3 is divisible by 3 but not 2
    4 is even
    5 is boring
    6 is even
    exit the loop!
    8 is boring
    9 is boring
    ```

- Blank Switches
    ```go
    words := []string{"go", "there", "is", "a", "playground"}
    for _, word := range words {
        switch wordLen := len(word) {
            case wordLen < 5:
                fmt.Println("less than 5")
            case wordLen > 10:
                fmt.Println("greater than 10")
            default:
                fmt.Println(word)
        }
    }
    ```
    ```go
    switch {
        case a == 2:
            fmt.Println("a", 2)
    }

    ```

## Chapter 5 : Functions
### Functions in Go
```go
func div(num int, deno int) int {
    if deno == 0 {
        return 0
    }
    return num / deno;
}

func div(num, deno int) int {
    ...
}
```
- Go doesn't supports **named** and **optional** input parameters. You must use struct to the same
```go

type MyFuncOpts struct {
    FirstName string
    LastName string
    Age      int 
}

func myFunc(opts MyFuncOpts) error {

}

func main() {
    MyFunc(MyFuncOpts{
        LastName : "Sharma",
        Age : 10
    })
}
```

- Variadic Input Parameters and Slices

```go
func addTo(base int, vals ...int) []int {
    out := make([]int, 0, len(vals))
    for _, v := range vals {
        out = append(out, base + v)
    }
    return out
}

// must put ... after literals, slices

func main() {
    fmt.Println(addTo(3))
    fmt.Println(addTo(3, 4))
    fmt.Println(addTo(3, 2, 3, 4, 5, 5, 5))
    a := []int{4, 3} 
    fmt.Println(addTo(3, a...))
    fmt.Println(addTo(3, []int{1, 2, 3, 4}...))
}

```

- Multiple value return from a method (different feature from other lang)
```go
func divAndRemainder(num, denom int) (int, int, error) {
    if denom == 0 {
        return 0, 0, errors.New("can't divide by zero");
    }
    return num / denom, num % denom, nil
}

// must assign each value to a variable

func main() {
    result, remainder, error := divAndRemainder(5, 2)
    if error != nil {
        fmt.Println(error)
        os.Exit(1)
    }
    fmt.Println(result, remainder)
    // you can also ignore return value by using _
}
```

- Named return value (must be within parenthesis, even if single)
```go
// these variables becomes the pre-declared variable within the scope of 
// method and makes code more intuitive/readable compare to just return type
func divAndRemainder(num, denom int) (result int, remainder int, err error) {
    if denom == 0 {
        err = errors.New("cannot divide by zero")
        return result, remainder, err
    }
    result, remainder = num/denom, num%denom
    return result, remainder, err
}
```
- Function in Go are values 
- The default value for function variable is `nil`
- Attempting to run a method with `nil` value results in a panic 
```go
func f1 (a string) int {
    return len(a)
}

func f2 (a string) int {
    total := 0
    for _, v := range a {
        total += int(v)
    }
    return total
}

func main() {
    var myFuncVariable func(string) int
    myFuncVariable = f1
    result := myFuncVariable("hello")
}
```
### Example of use of Go function as value
```go
func add(i, j int) int { return i + j}
func sub(i, j int) int {return i - j}
func mult(i, j int) int {return i * j}
func div(i, j int ) int {return i / j}

var opMap = map[string]func(int, int) int {
    "+" : add,
    "-" : sub,
    "*" : mult,
    "/" : div,
}

func main() {
    expression := [][]string {
        {"2", "+", "3"},
        {"3", "-", "2"},
    }

    for _, expression := range expressions {
        if len(expression) != 3 {
            fmt.Println("Invalid expression ", expression);
            continue
        }
        p1, err := strconv.Atoi(expression[0])
        if err != nil {
            fmt.Println(err)
            continue
        }
        op := expression[1]
        opFunc, ok := opMap[op]
        if !ok {
            fmt.Println("unsupported operator : ", op)
            continue
        }
        p2, err := strconv.Atoi(expression[1])
        if err != nil {
            fmt.Println(err)
            continue
        }
        result := opFunc(p1, p2)
        fmt.Println(result)
    }

}

```

### Function type declaration
```go
// helps you name and refer this better / documentation
type opFuncType func(int, int) int

var opMap = map[string] opFuncType {
    ...
}
```

### Anonymous function
```go
func main() {
    f := func(j int) {
        fmt.Println("printing ", j, "from inside f")
    }
    for i := 0; i < 5; i++ {
        f(i)
    }
}

// Another way
func main() {
    for i := 0; i < 5; i++ {
        f := func(j int) {
            fmt.Println("printing ", j, "from inside f")
        }(i)
    }
}

// Since you can declare variables at the package scope, you can also declare package scope
// variable that are assigned anonymous function

var (
    add = func (i, j int) int {return i + j}
    sub = func (i, j int) int {return i - j}
)

func main() {
    x := add(2, 3)
    fmt.Println("x ", x)
    changeAdd()
    y := add(2, 3)
    fmt.Println("y ", y)
}

// unlike a normal function definition, you can assign a new value to a package-level anonymous function

func changeAdd() {
    add = func (i, j int) int {return i + i + j + j}
}
```

> Note that package level anonymous functions must be immutable in nature (recommended)

- Closures
    - Functions declared inside functions are special; they are **closures**
    - Inside function are able to access and modify variables declared in the outer function
    ```go
    func main() {
        a := 20
        f := func() {
            fmt.Println(a)
            a = 30 // if done a := 30, then it is shadowing (new variable)
        }
        f()
        fmt.Println(a)
    }
    ```

- Use case of closures ? or these mini-functions ?
    - Limits a function scope (only to outer function)
    - If a function is going to be called from only one other function, but its called multiple time, you can use inner function to hide the called function

- Passing Functions as Parameters
    - Use case ? - Popular one - Sort method
    - Middlewares
    - Function taking function as input : Higher order function (in Haskell)
    ```go
    type Person struct {
        FirstName string
        LastName string
        Age int
    }

    people := []People {
        {"Chintan", "Seth", 30},
        {"Ronak", "Ladhar", 32},
        {"Sourav", "Sharma", 28},
    }

    fmt.Println(people)

    sort.Slice(people, func(i, j int) bool {
        return people[i].LastName < people[j].LastName
    })

    sort.Slice(people, func(i, j int) bool {
        return people[i].Age < people[j].Age
    })
    ```

- Returning method from the method 
```go
func makeMult(base int) func(int) int {
    return func(factor int) int {
        return base * factor
    }
}

func main() {
    twoBase := makeMult(2)
    threeBase := makeMult(3)

}
```

- Defer
    - Go also uses closures to implement resource cleanup, via the `defer` keyword
    - Programs often creates temporary resources, like file or network connections, that need to be cleanup
    - This cleanup has to happen, no matter how much exit points a function has, or whether a function completes successfully or not 
    - In Go, cleanup code is attached to the function with the `defer` keyword
    > The defer keyword in Go delays the execution of a function until the surrounding function exits
    ```go
    import (
        "io"
        "log"
        "os"
    )
    func main() {
        if len(os.Args) < 2 {
            log.Fatal("no file specified")
        }
        f, err := os.Open(os.Args[1])
        if err != nil {
            log.Fatal("err := ", err)
        }
        defer f.Close()
        data := make([]byte, 2048)
        for {
            count, err := f.Read(data)
            os.Stdout.Write(data[:count])
            if err != nil {
                if err != io.EOF {
                    log.Fatal(err)
                }
                break
            }
        }
    }
    ```
    ```go
    func deferExample() int {
        a := 10
        defer func(val int) {
            fmt.Println("first:", val)
        }(a)
        a = 20
        defer func(val int) {
            fmt.Println("second", a)
        }(a)
        
        // You can supply a function that return value to a defer, but there's no way to read those values (use named)
        defer func() int {
            return 2
        }()

        a = 30
        fmt.Println("a", a)
        return a
    }

    // Because Go doesn't allow unused variable, returning the closer from the function means that the program will not compile if the function is not called.

    func getFile(name string) (*os.File, func(), error) {
        file, err := os.Open(name)
        if err != nil {
            return nil, nil, err
        }
        return file, func() {
            file.Close()
        }, nil
    }

    func main() {
        f, closer, err = getFile(os.Args[1])
        if err != nil {
            log.Fatal(err)
        }
        defer closer() // note the parenthesis after closer
    }
    ```

### Go is CALL BY VALUE
- Go always makes a copy of the value of the variable, when passed for a parameter to a function
```go
type person struct {
    age int
    name string
}

func modifyFails(i int, s string, p person) {
    i = i * 2
    s = "changed"
    p.name = "bob"
}

func main() {
    p := person{}
    s := "alice"
    i := 3
    modifyFails(i, s, p) // no changes to i, s, p after call

}
```
- Modify the Map and Slice 
```go   
func modMap(m map[int]string) {
    m[2] = "hello"
    m[3] = "dummy"
    delete(m, 1)
}
func modSlice(s []int) {
    for k, v := range s {
        s[k] = v * 2
    }
    s = append(s, 10) // can't lengthen the slice
}

func main() {
    m := map[int]string {
        1 : "one",
        2 : "two",
    }
    modMap(m)
    fmt.Println(m) // map[2:hello 3:dummy]

    s := []int{1, 2, 3}
    modSlice(s)
    fmt.Println(s) // [2 4 6]
}

- Slices and Maps are different that other type, why ? because they are implemented using pointer
```
> Every type in Go is a value type. It's just that something the value is a pointer
> Call by value is the reason, Go limited support for constants (since variable are passed by value)


## Chapter 6 : Pointers in GO
### Pointer
- A pointer is a variable that holds the location in memory where a value is stored
- Pointer sizes are fixed, no matter what type they are pointing (typically 4-byte, or sometime 8-byte)
```go
var x int32 = 10
var y bool = true
pointerX := &x
pointerY := &y
var pointerZ *string
```
- The zero value of a pointer is nil (unlike `NULL` in C, `nil` is not another name for 0; you can't convert it back and forth with a number). `nil` is an untyped indentifier that represent the lack of a value for certain type

> Nil is value defined in universe block, it can be shadowed. Never name a variable or function nil

- Unlike C, **NO** pointer arithmetic is allowed in Go :(
- Memory management pain is also gone, since Go has a garbage collector

```go
x := "hello"
pointerToX := &x
```

- The `*` is the *indirection* operator. 
```go
x := 10
pointerToX := &x
fmt.Println(pointerToX) // print a memory address
fmt.Println(*pointerToX) // print 10
z := 5 + *pointerToX
fmt.Println(z)
```

- If dereference a `nil` pointer, then code will panic at runtime
```go
x := 10
var pointerToX *int
pointerToX = &x

var x = new(int) // new creates a pointer variable, with 0 value
fmt.Println(x == nil)
fmt.Println(*x) // 0
```
- You can't use `&` with the primitive literal(number, booleans, and string) or a constant because they don't have memory addresses; they exist only at compile time.


```go
type person struct {
FirstName  string
MiddleName *string
LastName   string
}

p := person{
FirstName:  "Pat",
MiddleName: "Perry", // This line won't compile
LastName:   "Peterson",
}

// so ? 

func makePointer[T any](t T) *T{
    return &t
}

p := person{
FirstName:  "Pat",
MiddleName: makePointer("Perry"), // This works
LastName:   "Peterson",
}

// Why above work ? remember copy-as-value ? The parameter address is returned back
```

### Pointers indicate Mutable Parameters
> MIT’s course on Software Construction sums up the reasons: “[I]mmutable types are safer from bugs, easier to understand, and more ready for change. Mutability makes it harder to understand what your program is doing, and much harder to enforce contracts.
- Go : Choice b/w value and parameter types addresses the issue
- 
- Since Go is a call-by-value language, the values passed to functions are copies. 
- For nonpointer types like primitives, structs, and arrays, this means that the called function cannot modify the original. 
- Copy == data’s immutability is guaranteed
- If a pointer is passed to a function, the function gets a copy of the pointer. This still points to the original data, which means original data can be modified by the called function
```go

func failedToUpdate(g *int) {
    x := 10
    g = &x
}

func update(g *int) {
    *g = 20
}
func main() {
    var f *int // f is nil
    failedToUpdate(f)
    fmt.Println(f) // f is nil 
    x := 10
    f = &x
    update(f)
    fmt.Println(x) // x is 20
}

```
## Chapter 7 : Type, Methods, and Interfaces

- Go allows you to attach method to the types
```go
type Person struct {
    FirstName string
    LastName string
    Age int
}
```
- Use any primitive type or compound type literal to define a concrete type
- Go allows declaring a type at any block level 
```go
type Score int
type Converter func(string)Score
type TeamScores map[string]Score
```


- Method on user defined type
- Method definition looks similar to function declarations, with one addition: the receiver specification
    - Method = Func + Receiver Specification
- The reciver specification = [ Struct | Named Type ]
- Method allows you define/attach behavior to a specific type (OOPs)
- Example : 
```go
type Person struct {
    FirstName string
    LastName string
    Age int
}

func (p Person) String() string {
    return fmt.Sprintf("%s %s, age %d", p.FirstName, p.LastName, p.Age)
}

p := Person {
    FirstName : "Sourav",
    LastName : "Sharma",
    Age : 24
}

output := p.String()
```

- Diff b/w func and Method ? 
    - Method can be defined at package block level, while function can be defined inside any block
- Just like function, method names cannot be overloaded
    - This is different from other Object Oriented Languages


### Pointer receivers and value receivers 
- If you method modify the receiver, you must use a pointer receiver
- If your method needs to handle `nil` instances, then it must use a pointer receiver
- If you method doesn't modify the receiver, you can use a value receiver
> A common practice in Go is to use pointer receiver all the time, whether modify or not modify (consistent) (:surprise why ?)
- Example
```go
type Counter struct {
    total int
    lastUpdated time.Time
}

func (c *Counter) Increment() {
    c.total++
    c.lastUpdate = time.Now()
}

func (c Counter) String() string {
    return fmt.Sprintf("total : %d, last updated : %v", c.total, c.lastUpdate)
}

```

- If you call a value receiver on a pointer variable e.g. `c.String()`, where `c` is a pointer type variable and method `String()` is value receiver, Go automatically dereference the pointer when calling the method
    - `c.String()` -> `(*c).String()`
    ```go
        c := &Counter{}
        fmt.Println(c.String())
        c.Increment()
        fmt.Println(c.String())
     ```
- If you call a pointer receiver on a value type e.g. `c.Increment()`, where `c` is a value type variable and method `Increment()` is a pointer receiver, Go automatically takes the address of the local variable when calling the method.
    - `c.Increment()` -> `(&c).Increment()`
    ```go
    var c Counter
    fmt.Println(c.String())
    c.Increment()
    fmt.Println(c.String())
    ```

> If your code call a value receiver method with a pointer instance whose value is `nil`, your code will compile, but will panic at runtime

- Rules of passing value to functions still apply (copy)
```go
func doUpdateWrong(c Counter) {
    c.Increment()
    fmt.Println("in doing update wrong", c.String());
}

func doUpdateRight(c *Counter) {
    c.Increment()
    fmt.Println("in doing update right", c.String());
}

func main() {
    var c Counter
    doUpdateWrong(c)
    fmt.Println("in main: ", c.String())
    doUpdateRight(c)
    fmt.Println("in main: ", c.String())
}

/* Output:
in doUpdateWrong: total: 1, last updated: 2009-11-10 23:00:00 +0000 UTC
    m=+0.000000001
in main: total: 0, last updated: 0001-01-01 00:00:00 +0000 UTC
in doUpdateRight: total: 1, last updated: 2009-11-10 23:00:00 +0000 UTC
    m=+0.000000001
in main: total: 1, last updated: 2009-11-10 23:00:00 +0000 UTC m=+0.000000001
*/
```

- Go considers both pointer and value receiver methods to be in the method set for a pointer instance.
- For a value instance, only the value receiver methods are in the method set.


### Code you method for `nil` Instances

- What happen when you call a method on `nil`.
    - If it's a method with value receiver, then you'll get a panic, since there is no value pointed by the pointer
    - If it's a method with pointer receiver, it can work if the method is written to handle the possibility of a `nil` instance


```go
type Tree struct {
    val int
    left, right *Tree
}

func (itr *Tree) Insert(val int) *Tree {
    if itr == nil {
        return &Tree{val: val}
    }
    if val < itr.val {
        itr.left = itr.left.Insert(val)
    } else if val > itr.val {
        itr.right = itr.right.Insert(val)
    }
    return itr;
}

func (itr *Tree) Contains(val int) bool {
    switch {
        case itr == nil:
            return false
        case val < itr.val:
            return itr.left.Contains(val)
        case val > itr.val:
            return itr.right.Contains(val)
        default:
            return true
    }
}

func main() {
    var it *IntTree
    it = it.Insert(5)
    it = it.Insert(3)
    it = it.Insert(10)
    it = it.Insert(2)
    fmt.Println(it.Contains(2))  // true
    fmt.Println(it.Contains(12)) // false
}

```

- But remember, that pointer receivers are same as pointer function instance, which means both variables point to the same object, but if you make changes to the receiver variable that doesn't make any changes to the original.
- You can’t write a pointer receiver method that handles nil and makes the original pointer non-nil.


### Methods are function too

```go

type Adder struct {
    start int
}

func (a Adder) AddTo(val int) int {
    return a.start + val
}

myAdder := Adder{start: 10}
fmt.Println(myAdder.AddTo(5)) // 15

f1 := Adder.AddTo

fmt.Println(f1(10)) // 20

// A method value is like a closure, since it can access the values in the fields of the instance from which it was created

f2 := Adder.AddTo
fmt.Println(f2(myAdder, 15)) // 25

```

### Function Vs Method
- If logic depends only on the input parameter, it should be a function
- Anytime your logic depends on values that are configured at startup or changed while your program is running, those value should be store in a struct, and that logic should be implemented as a method


### Type declarations aren't inheritance

- A type on a type - But this is not a inheritance
```go
type HighScore Score
type Employee Person
```
- You can't assign an instance of type HighScore to Score, or vice versa

### Types Are Executable Documentation 
- They make code more clear when you should declare a user-defined type based on other built-in types or one user-defined type that's based on another 
- It's clearer for someone reading a parameter of type `Percentage` than of type `int`

### iota Is for Enumerations - Sometimes
- Similar to `enum`, which allow you to specify that a type can only have a limited set of values
- Go doesn't have `enumeration` type. Instead it has `iota`, which lets you assign an increasing value to a set of constant.

- When using `iota`, the best practice is to first define a type on `int` that will represent all the values:
```go
type MailCategory int
const (
    Uncategorized MailCategory = iota
    Personal
    Spam
    Social
    Advertisement
)
```
- Note that only `Uncategorized` constant has type defined i.e., `MailCategory` and its value set to `iota`
- Every subsequent line has neither the *type* and nor the *value* assigned to it. 
- Go compiler repeats the same for each line i.e., append `MailCategory = iota` 
- The value of `iota` increment for each constant defined in the const block, starting with `0`
- Only use `iota` when you know that constant doesn't have a true value. The value `0..n` are only for internal purpose 
- If your constant take some value, the you should not use `iota`

```go
type BitField int

const (
    Field1 BitField = 1 << iota // assigned 1
    Field2                      // assigned 2
    Field3                      // assigned 4
    Field4                      // assigned 8
)
```
- But be careful with the above code.

### Embedded fields
```go

type Employee struct {
    Name string
    ID   string
}

func (e Employee) Description() string {
    return fmt.Sprintf("%s (%s)", e.Name, e.ID);
}


type Manager struct {
    Employee // Embedded field
    Reports []Employee
}

func (m Manager) FindNewEmployee() []Employee {
    // do business logic
}

m := Manager {
    Employee :Employee {
        Name: "adumbc",
        ID: "1234",
    }
    Reports: []Employee{},
}

fmt.Println(m.ID)
fmt.Println(m.Description())
```

- The above is example of *embedded field*. The Manager struct contains Employee, but with no name
- This makes `Employee` an *embedded field*
- Any fields or method defined on an embedded field are *promoted* to the containing structure and can be direclty invoked on that
> You can embed any type within a struct, not just a struct. This promotes method on embedded type to the containing struct

```go

type Inner struct {
    X int
}
type Outer struct {
    Inner
    X int
}

o := Outer {
    Inner : Inner{
        X : 10,
    },
    X : 20,
}

fmt.Println("outer : ", o.X)
fmt.Println("inner : ", o.Inner.X)

```
### Embedding is not Inheritance
- Very rare to find this kind of thing in other langs
- This also might look you like inheritance, but NO
    - You can't assign a variable of type `Manager` to a variable of type `Employee`
    ```go
    var eFail Employee = m // compilation error!
    var eOK Employee = m.Employee // OK
    ```

- Go has no dynamic dispatch for concrete types
    - The methods on embedded field have no idea they are embedded, which means there is no dynamic dispatch can't be done as there is lack of knowledge
    ```go
    type Inner struct {
        A int
    }

    func (i Inner) IntPrinter(val int) String {
        return fmt.Sprintf("Inner : %d", val)
    }

    func (i Inner) Doube() String {
        return i.IntPrinter(i.A * 2)
    }


    type Outer struct {
        Inner
        S string
    }

    func (o Outer) IntPrinter(val int) String {
        return fmt.Sprintf("Outer : %d", val)
    }

    func main() {
        o := Outer {
            Inner : Inner {
                A : 10,
            },
            S : "hello",
        }
        fmt.Println(o.Double()) // prints Inner: 20
    }
    ```
### Short to Inteface
- Most popular feature of GO (real star of GO)
- By convention interface names end with `er`
```go

type Counter struct {
    total int
    lastUpdated time.Time
}

func (c *Counter) Increment() {
    c.total++
    c.lastUpdate = time.Now()
}

func (c Counter) String() string {
    return fmt.Sprintf("total : %d, last updated : %v", c.total, c.lastUpdate)
}


// --- 

// from fmt package (Stringer interface)
type Stringer inteface {
    String() string
}

type Incrementer interface {
    Increment();
}


var myStringer fmt.Stringer
var myIncrementer Incrementer

pointedCounter := &Counter{}
valueCounter := Counter{}

myStringer = pointerCounter // ok
myStringer = valueCounter // ok

myIncrementer = pointerCounter // ok
myIncrementer = valueCounter // compile-time error!

```

### Interface are Type-Safe Duck Typing
- Interface in Go looks similar to other language but with one diff
- Note in the above `Counter` and `Incrementer`. There is no where in the `Counter` (a concrete type) struct we have specified that this *implements* the interface
- If the method set for concrete type contains all the method in the method set for an interface, the concrete type implements the interface
- This implicit behavior make interfaces most interesting!!
    - Enables type safety and decoupling 
    - Bridge the functionality in both static and dynamic language
    - Allows you to swap implementation as needed

> Duck Typing - "if it walks like a duck and quacks like a duck, it's a duck" - Used a lot in dynamic typed language like Python, Ruby, and Javascript that don't have interfaces.  The concept is that you can pass an instance of a type as a parameter to a function as long as the function can find a method to invoke that it expects:

- Python
```python
class Logic:
    def process(self, data):
        # business logic

def program(logic):
    # get data from somewhere
    logic.process(data)

logicToUse = Logic()
program(logicToUse)
```

- Java
```java
public interface Logic {
    String process(String data);
}

public class LogicImpl implements Logic {
    public String process(String data) {
       // business logic ...
    }
}


public class Client {
    private final Logic logic;
    public Client(Logic logic) {
        this.logic = logic;
    }
    public void program() {
        this.logic.process(data);
    }
}

private static void main(String[] args) {
    Logic logic = new LogicImpl();
    Client client = new Client(logic);
    client.program();
}

```

```go
type LogicProvider struct {}
func (lp LogicProvider) Process (data string) string {
    // business logic
}

type Logic interface {
    Process(data string) string
}

type Client struct {
    L Logic
}
func (c Client) Program() {
    c.L.Process(data)
}

main() {
    c := Client {
        L : LogicProvider{},
    }
    c.Program()
}

```


> Interfaces specify what callers need. The client code defines the interface to specify what functionality it requires.

### Decorator pattern
- Common in go to write factory methods 
    - IN: An instance of a interface 
    - OUT: return another type that implement the same interface


```go
func process(r io.Reader) error

r, err := os.Open(fileName)
if err != nil {
    return err
} 
defer f.Close()
return process(r)

```

- Wrapper 

```go
r, err := os.Open(fileName)
if err != nil {
    return err
}
defer r.Close()
gz, err := gzip.NewReader(r)
if err != nil {
    return err
}
defer gz.Close()
return process(gz)

```

- It’s perfectly fine for a type that meets an interface to specify additional methods that aren’t part of the interface. 
    - Use case ?
        - One set of client (say) may not care about those methods, but other do
        - e.g. `io.File` *type* also meets the `io.Writer` *interface* 



### Embeddings and Interfaces

- Embeddings is not only for `structs`
- You can embed an interface in an interface

```go
type Reader interface {
    Read(p []byte) (n int, err error)
}

type Closer interface {
    Close() error 
}

type ReadCloser interface {
    Reader
    Closer
}

```
- Later we will also see that we can embed an interface in a struct


### Accept Interfaces, Return Structs

- Means ? 
    - Business logic invoked by your functions should be invoked via intefaces
    - But the output of your function should be *concrete* type

- Interfaces makes your code more flexibile (independent of implementation) 

- Why return concrete ? 
    - When a concrete type is returned by a function, new methods and fields and methods are ignored
    - Not true for interfaces
        - Adding a new method to interface means that all existing implementations of that interface must be updated
    - Avoids backward compatiabitity issues


> Write separate factory method for each concrete type

- In some situation, it's unavoidable and you have no choice but to return an interface 
    - Erros are an exception to this rule 
    - This bears some cost to the garbage collection, since returning struct avoids the heap allocation
    - However, when invoking a function with the parameter of interface type, a heap allocation occurs for each interface parameter
    - 



### Interfaces and nil

- `nil` : Zero value for
    - pointer type 
    - Inteface type  (but not as simple as it was for concrete type)

- Understanding how Go implements inteface
    - a struct with two fields
        - 1 : value
        - 2 : type of value
    - As long as type field(2) is non-nil, interface is non-nil
    - In order for an interface to be considered as `nil`, both the type and value must be `nil` 
    ```go
    var pointerCounter *Counter 
    fmt.Println(pointerCounter == nil) // true

    var incrementer Incrementer 
    fmt.Println(incrementer == nil) // true

    incrementer = pointerCounter
    fmt.Println(incrementer == nil) // false
    ```
    - `nil` indicates : whether you can invoke method on it or not
    - If interface is `nil` + method invoke = panic 
    - Allowed: You can have concrete type still `nil`, but note code can still panic if those method not handle `nil`

### Interfaces Are Comparable
- If type and values are equal -> interfaces are equal
```go

type Doubler interface {
    Double()
}

type DoubleInt int 

func (d *DoubleInt) Double() {
    *d = *d * 2
}

type DoubleIntSlice []int

func (d DbouleIntSlice) Double() {
    for i := range d {
        d[i] = d[i] * 2
    }
}

func DoublerComparator(d1, d2 Doubler) {
    fmt.Println(d1 == d2)
}

var di DoubleInt = 10
var di2 DoubleInt = 10
var dis = DoubleIntSlice{1, 2, 3}
var dis2 = DoubleIntSlice{1, 2, 3}

DoubleComparator(&di, &di2) // false : type match, but you are comparing pointer, not values
DoubleComparator(&di, dis) // false : type not match
DoubleComparator(dis, dis2) // compile, but run time panic (slices are not comparable)

// Also we aware that they key of map must be comparable, so a map can be defined
// to have an key as interface

m := map[Doubler]int{}

```

> `Interface{}` isn't special case syntax. An empty interface type simply state that type can store any value whose type implements zero or more methods. This just happens to to match every type in Go


- Go added `any` as type alias for `interface{}`. Because an empty inteface doesn't tells you anything about the value it represent.
- One common use of `any` is a placeholder for data of uncertain schema that's read from external store

```go
data := map[string]any{}
content, err := os.ReadFile("testdata/sample.json")
if err != nil {
    return err
}
json.Unmarshal(content, &data)

```
- But avoid using `any` and stay with the strict type 
- When you store a value in an empty interface, how to read that ? 
    - Type assertions and Type switches

### Type Assertion and Type Switches

- A type assertion names the concrete type that implements the interface 

```go
type MyInt int 

func main() {
    var i any
    var mine MyInt = 20
    i = mine
    i2 := i.(MyInt)
    fmt.Println(i2 + 1)

    i2 := i.(string) // code will panic

    // To avoid panic use comma ok idiom

    i2, ok = i.(int)
    if !ok {
        return fmt.Errorf("unexpected type for %v", i)
    }
    fmt.Println(i2)
}
```

- A type assertion is different from type conversion. 
    - Type conversion changes a value to the new 
    - Assertion reveals the value stored in the interface
    - All type assertions are checked at runtime, so must use comma ok idiom
    - When an interface could be one of the multiple possible types, use a `type` switch instead
    ```go
    func doThings(i any) {
        switch j := i.(type) {
            case nil:
            case int:
            case MyInt:
            case io.Reader:
            case string:
                // j is type of string
            case bool, rune:
                // j is type of any
            default:    
                // no idea, so j is of type any
        }
    }
    ```

> While getting the concrete implementation from the interface variable might seems handy, you should use these technique infrequently

- Use case ? 
    - To check if the concrete type behind the interface, implements some other inteface 
    - This allows you to specify the optional interface 

    - ex. Standard library use this technique to allow more efficient copy
    ```go
    func copyBuffer(dst Writer, src Reader, buf[] byte) (written int64, err error) {
        if wt, ok := src.(WriterTo); ok {
            return wt.WriteTo(dst)
        }
        if rt, ok := dst.(ReadFrom); ok {
            return rt.ReadFrom(src)
        }
    }

    ```

- Type switch statement
    - Ability to differentiate b/w multiple implementation of an interface
      that requires different processing
    ```go
    func walkTree(t *treeNode) (int, error) {
        switch val := t.val.(type) {
            case nil: 
                return 0, errors.New("invalid expression")
            case number:
                return int(val), nil
            case operator:
                left, err := walkTree(t.lchild)
                if err != nil {
                    return 0, nil
                }
                right, err := walkTree(t.rchild) 
                if err != nil {
                    return 0, nil
                }
            default: 
                return 0, errors.New("unknown node type")
        }
    }

### Function Type are Bridge to Interfaces
- You see we define method on a struct (user defined type)
- What if we have user defined type with an underlying type `int`, `string` ? 
    - One POV - `int` and `string` are also holding some sort of state, and business logic inside method interact with the state
- Go allows to define method on any *user-defined* type 
- Is it a flaw ?
    - Not actually
    - This is very helpful in some cases 
    - They allow function to implement interfaces 
        - Most common use is **HTTP Hanlder**
        - An HTTP handler process an HTTP server request defined via an interface
    ```go
    type Handler interface {
        ServerHTTP(http.ResponseWriter, *http.Request) 
    }

    // by using type conversion to `http.HandlerFunc`, any function that has same signature
    // can be used as http.Handler

    type HandlerFunc func(http.ResponseWriter, *http.Request) 

    func (f HandlerFunc) ServeHTTP(w http.ResponseWriter, r *http.Request) {
        f(w, r)
    }
    ```
- When to use 
    - Inteface VS
    - function/method specify an input param as function type 
- If your single function is likely to depend on many other functions or other state that's not specified in the input paramter, use interface parameter and define a function type to bridge a function to their interface
- If simple function like `sort.Slice` then parameter of a function type is good choice

### Implicity Interface makes Dependency Injection Easier
- Software enginerres talks about *decoupling* code, so that changes effect the least code
- One of the technique to achive decoupling is *dependency injection* 
- Dependency injection is the concept that your code should explicitly specify the functionality it needs to perform its task
> Dependency injection might be pain in other languages, but GO do it easily without any libraries

- Example of Implicit Interfaces to compose application via dependency injection
    ```go
    // logger
    func LogOutput(message string) {
        fmt.Println(message)
    }
    // data store
    type SimpleDataStore struct {
        userData map[string]string
    }

    func (sds SimpleDataStore) UserNameForID(userID string) (string, bool) {
        name, ok := std.userData[userID]
        return name, ok
    }

    // factory method to create instance of SDS

    func NewSimpleDataStore() SimpleDataStore {
        return SimpleDataStore {
            userData : map[string] string {
                "1": "Red",
                "2": "Green",
                "3": "Blue"
            }
        }
    }

    // some business logic
    // looks up the user and say hello/bye
    // You also want your business logic to log when invoked, so it depends on a logger
    // However, you don't want to force it to depend on `LogOutput` or 
    // `SimpleDataStore`, because you might want to use different logger or data
    // store 

    // Business logic interface, on what it depends
    type DataStore interface {
        UserNameForID(userID string) (string, bool)
    }

    type Logger interface {
        Log(message string)
    }

    // to make you LogOutput function meet this inteface, you define a function type with a method on it

    type LoggerAdapter func(messsage string)

    func (lg LoggerAdapter) Log(message string) {
        lg(message)
    }

    // Dependency defined, now lets look at the bussiness logic

    // simple business logic 
    type SimpleLogic struct {
        l Logger
        ds DataStore
    }

    func (sl SimpleLogic) SayHello(userID string) (string, error) {
        sl.l.Log("in sayHello for " + userID)
        name, ok := sl.ds.UserNameForID(userID)
        if !ok {
            return "", errors.New("unknown user")
        }
        return "Hello, " + name, nil
    }

    func (sl SimpleLogic) SayGoodBye(userID string) (string, error) {
        sl.l.Log("in SayGoodBye for " + userID)
        name, ok := sl.ds.UserNameForID(userID)
        if !ok {
            return "", errors.New("unknown user")
        }
        return "Goodbye, " + name, nil
    }

    ``` 

- Note that in `SimpleLogic` nothing is defined about the concrete types, so there is no dependency on them
- There is no problem if you later swap in some new implementation
- Thus provider and interface are separate
- So this makes it different from *explicit interface* in language like Java
    - Even though Java uses interface to decouple the implementation from the inteface
    - Explicit intefaces is one which binds client and provider together

- Example contd. : Let say a single endpoint you define `/hello`, which say hello to the person


```go
type Logic interface {
    SayHello(userID string) (string, error)
}

// Note that in above, SayHello method is available to you SimpleLogic struct,
// but once again, the concrete type is not aware of the inteface
// Further more the other method on SimpleLogic, SayGoodBy, is not in the above inteface
// because you controller doesn't care about this 
// The above interace is owned by client, so it's method set is customized to the need of
// client code

type Controller struct {
    l Logger
    logic Logic 
}


func (c Controller) SayHello(w http.ResponseWriter, r *http.Request) {
    c.l.Logger("In SayHello")
    userID := r.URL.Query().Get("user_id") // assuming simple for now
    message, err := c.logic.SayHello(userID)
    if err != nil {
        w.WriteHeader(http.StatusBadRequest)
        w.Write([]byte(err.Errors()))
        return
    }
    w.Write([]byte(message))
}

// factory function for controller

func NewController(l Logger, logic Logic) Controller {
    return Controller {
        l: l,
        logic: logic,
    }
}

// finally

func main() {
    l := LoggerAdapter(LogOutput)
    ds := NewSimpleDataStore()
    logic := NewSimpleLogic(l, ds)
    c := NewController(l, logic)
    http.HandleFunc("/hello", c.SayHello)
    http.ListenAndServe(":8000", nil)
}
```