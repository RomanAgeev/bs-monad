exception Test_Error(string);

let () = {
    open PromiseMonad.Make;
    open PromiseMonad.Ex;
        
    let _ = return(10)
        >>= (x => return(x * 2))
        >>= (y => {
            if (y < 25) {
                string_of_int(y) |> print_endline;
                return();
            } else {
                throw(Test_Error("too large"));
            }
        })
        >>| (error => {
            Js.log2("Falure !!", error);
            return()
        });
};

module ContinuationMonad = ContMonad.Make({ type t = string; });
module ContinuationEx = Monad.Ex(ContinuationMonad);

let () = {
    open ContinuationMonad;
    open ContinuationEx;

    let pipe = return(x => x + 1)
        >>= (f => return(x => f(x * x)))
        >>= (f => return(f(4)))
        |> extract;

    pipe(string_of_int) |> print_endline;
};