# General Notes

## Basics
Go code <- packages <- Go files __in a directory__

`package main` is for executable program only and `func main() {}` is the entry point of the program.

Newlines with certain tokens is similar with semicolons in C. Therefore, where to break lines is significant.

### Command Arguments
`os.Args` -> a slice of strings. `os.Args[0]` is the program name.

### Variable and Const
```
s := ""
var s string
var s = ""
var s string = ""
var i, j, k int                 // int, int, int
var b, f, s = true, 2.3, "four" // bool, float64, string
var f, err = os.Open(name) // os.Open returns a file and an error
i, j = j, i // swap values of i and j
```
If not value is provided to initialize the varialbe, __zero value__ is used. 

Notice that `:=` is different from `=` assignment.

"One subtle but important point: a short variable declaration does not necessarily
declare all the variables on its left-hand side. If some of them were already 
declared in the __same lexical block (§2.7)__, then the short variable declaration 
acts like an assignment to those variables."
-- The Go Programming Language
```
const (
    C1 = 0
    C2 = 1
)
const C1 = 0
```

#### Lifetime
"The lifetime of a package-level variable is the entire execution of the program. 
By contrast, local variables have dynamic lifetimes: a new instance is created 
each time the declaration statement is executed, and the variable lives on until
it becomes unreachable, at which point its storage may be recycled. Function 
parameters and results are local variables too; they are created each time 
their enclosing function is called."
-- The Go Programming Language

### Zero Value
numbers: 0
boolean: false
string: ""
interface: nil
reference types (slice, pointer, map, channel, function): nil

"in Go there is no such thing as an uninitialized variable."
-- The Go Programming Language.
### struct

A `struct` can be initialized with _composite literals_, like `gif.GIF{...}`. 
Fields that are not set have __zero value__.
### If & Switch
```
if i > 0 {

} else if i = 0 {

} else {

}
```
```
switch s {
case "a":
    // no fallthrough
    a++
case "b":
    b++
default:
    c++
}
switch {
case i > 0:
    a++
default:
    b++
}
```


### Loop
```
for i := 0; i < 10; i++ {

}
```
```
for i < 10 {

}
```
```
for {
    // infinite
}
```
```
for idx, val := range os.Args[1:] {
    // range usage
}
for range os.Args[1:] {
    // just for number of iterations
}
```

Better not to use variables between `for` and `{` in a function value inside
the loop body. Why? The function value will capture the variables, however, 
the variables will be updated in each iteration. As loop body is itself a 
block scope, one can assign those variables to variables inside the loop body
to be captured inside a function value.

See 5.6.1 in The Go Programming Language

### Naming & Visibility
Naming is related to visibility at package level in Go. A name begins with a 
upper-case letter will be exported by its package, including struct, interface,
function, variable and method. Unexported fields in struct can be accessed
within the package, but not outside of the package. 

Naming style lean towards simple names for local variables, camel case for 
composite names and acronyms are rendered in the same case (such as "html" or 
"HTML").

### Pointer
It is okay to return the address of an local variable in a function. Each call 
to the function yields a different address (different variable therefore).

`new` can create a pointer to a unamed variable of a specific type, such as
`p := new(int)`. The initial value is __zero value__. Not used often though,
as the following is used:
```
p := &Point{1, 2}
// equals to
p := new(Point)
*p = Point{1, 2}
```

### Assignment
Multiple variables can appear in an assignment. All expressions on right-hand
side are evaluated before any variable is updated on the left-hand side, which
makes that we can do swap like `i, j = j, i`. 

### Conversion
```
type Celsius float64
type Fahrenheit float64
```
Conversion is available when types have the same underlying type,
`t := Celsius(10.0)`.

### Function
A named result list is allowed, all of which are initialized with __zero value__.

Default parameters are not supported and arguments are passed by value.

Function literal can be used within an expression, `func (arg) res {}`, anonymous
function.

### Method
A method can have a named type receiver or pointer to a named type receiver. 
However, named type receiver itself cannot have a pointer type as its underlying
type.

A method can be assigned to a variable. If the receiver is the type name, the
assigned variable can be called with the first argument as the receiver. 
```
foo := p.Distance
foo := Point.Distance    // foo(q, p)
foo := (*Point).Distance // foo(&q, p)
```

### Interface
A type T might not satisfy an interface, however *T might.

One can assign any value to the empty interface, even a value of basic type.

Interface is comparable and can be key of a map. Interface equals to `nil` when
both type and value are `nil`s. If its type is not and its value is, it does
not equal to `nil`. 

### Package & Import
"Within a Go program, every package is identified by a unique string called 
its import path." -- The Go Programming Language

An natural question is in what situation two files are in the same package?
My current assumption is they are in the same directory, so that `import` 
can indentify it. Also, they should declare the same `package` name. Usually,
one package in one directory, except we can have test package inside it. This
also means one package should not cover multiple directories. 

__Blank import__ comes with renaming a package as `_`. The package then is
initilized, but not used. Within the package's init, the package can register
itself to be refered by other packages.

#### Package Initialization
A `.go` file can have any number (including 0) of `func init() { }` to init
package-level variables. The `init` functions are called in the order of 
declaration. 

"A package with no imports is initialized by assigning initial values to 
all its package-level variables followed by calling all init functions in 
the order they appear in the source, possibly in multiple files, as presented 
to the compiler." -- Golang Spec

From what I understand, there is an order but not enforced. It really depends
on how the build system present files to the compiler.

## Common Data Structures
### Struct
Its zero value is composed of all fields with zero values. In this sense, it is
like an array, just that we can have name each element.

A struct cannot contain itself, but can contain itself's pointer. It is passed
by value.

A struct is comparable if all fields are comparable, like an array in this sense.

### String
It is a basic type in Go. It supports UTF-8 natively. However, built-in functions
`len` and `index` works on bytes instead of runes (characters?). `range` will
decode bytes into UTF-8 characters where index is still based on bytes:
```
for i, r := range "Hello, Image" {
    fmt.Printf("%d\t%q\t%d\n", i, r, r)
}
```

A string is immutable. `s[i:j]` will generate a new substring. `[]rune` can be
used to conversion a string into a slice of UTF-8 chars. `[]byte` and `string` 
can be converted between them. 

Comparison between two strings are done byte by byte.

`...` -> raw string to keep backslash, newlines etc.

### Array
fixed-size sequence, like `[3]int{1, 2, 3}` or `[...]int{1, 2}` or `[...]int{99:-1}`.
Two arrays are comparable if elements are comparable.

### Map
Keys are distinct and unordered. A map is passed by reference (regarding as a 
struct of pointer fields). 

One can look up a non-existence key whose value will be __zero value__, but `
val, ok = a_map[key]` can be used to check if a key really exists or not. One
cannot take address of an element of a map. 

## Goroutine
There is a goroutine leak. Goroutine should ensure it can terminate, otherwise
there is a leak which would not be garbage collected.

## Channels
channels are comparable. Two are equal when their references are same.

A channel can be closed for sending. Panic happens when sending again. Receiving
can still be going. When no more value sent, zero value will be received. `range`
can be used with channels to determine if it has been closed or not. 

Bidirectional channels can be converted to unidirectional channels implicitly,
but there is no way back.

Beware of a buffered channel of 1. With buffered channel, receiver and sender
are separated by the queue. Receiver and sender they communicate with the queue.


__unbuffered__
```
receiver <- sender
```

__buffered__
``` 
            [ ] <- sender
            [X]
receiver <- [X]
```

```
select {
case <-ch1:
    // ...
case x := <-ch2:
    // ...use x...
case ch3 <- y:
    // ...
default:
    // ...
}
// If multiple cases are ready, select picks one at random,
// It will block if no one is ready
// With default, it is like polling
```
