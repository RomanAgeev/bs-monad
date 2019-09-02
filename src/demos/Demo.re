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

let () = {
    open ListMonad.Make;
    open ListMonad.Ex;
    open Utils;

    let enumerate = (length: int) => {
        let rec aux = (~result=[], index) => index <= 0 ? result : aux(~result = [index, ...result], index - 1);
        aux(length);
    };

    let string_of_list = li => {
        let rec aux = (~result="", l) => switch l {
            | [] => result
            | [head, ...tail] => aux(~result = result ++ (result == "" ? "" : ", ") ++ head, tail)
        };
        "[" ++ aux(li) ++ "]";
    };

    enumerate(10) |> List.map(string_of_int) |> string_of_list |> print_endline;

    let first = enumerate >> make;
    let second = (x => [x * 2, x * -2]) >> make;
    let third = string_of_int >> return;
    let process = first >=> second >=> third;

    process(10) |> extract |> string_of_list |> print_endline;
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