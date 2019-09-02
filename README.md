# bs-monad

The project provides an implementation of all basic monads in ReasonML.

The following monads are available so far:

1. Writer Monad
2. Reader Monad
3. State Monad
4. List Monad
5. Option Monad
6. Promise Monad
7. Continuation Monad
8. Indentity Monad

## Example with fish (>=>) operator
```reason
module TestWriterMonad = WriterMonad.Make({
    type t = string;

    let mappend = (s1, s2) => s1 ++ ", then " ++ s2;
    let mempty = () => "";
});

module TestWriterMonadEx = Monad.Ex(TestWriterMonad);

let () = {
  open TestWriterMonad;
  open TestWriterMonadEx;

  let mult = x => make((x * 2, "Multiply by 2"));
  let plus = x => make((x + 2, "Plus 2")); 

  let process = mult >=> plus;

  let (res, log) = process(10) |> extract; // (22, "Multiply by 2, then Plus 2")
};
```

See [the tests](https://github.com/RomanAgeev/bs-monad/tree/master/__tests__) for more examples.
