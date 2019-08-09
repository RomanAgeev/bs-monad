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

module LoggerMonad = WriterMonad.Make({
    type t = string;

    let mappend = (s1, s2) => s1 ++ s2;
    let mempty = () => "";
});

module LoggerEx = Monad.Ex(LoggerMonad);

let () = {
    open LoggerMonad;
    open LoggerEx;

    let double = x => make((x * 2, " Double"));
    let tripple = x => make((x * 3, " Tripple"));
    let process = double >=> tripple;

    let (x, log) = process(2) |> extract;

    string_of_int(x) |> print_endline;
    print_endline(log);
};

module ProductMonad = ReaderMonad.Make({ type t = (string, string); });

module ProductEx = Monad.Ex(ProductMonad);

let () = {
    open ProductMonad;
    open ProductEx;

    let firstPlus = x => make(((e1, _)) => x ++ " " ++ e1);
    let secondPlus = x => make(((_, e2)) => x ++ " " ++ e2);
    let process = firstPlus >=> secondPlus;

    ("Roman", "Ageev") |> (process("Hello") |> extract) |> print_endline;
};

module NumberMonad = StateMonad.Make({ type t = int });

module NumberEx = Monad.Ex(NumberMonad);

let () = {
    open NumberMonad;
    open NumberEx;

    let inc = x => make(s => (x + s, s * 2));
    let process = inc >=> inc;

    let (result, state) = 2 |> (process(1) |> extract);
    "result " ++ string_of_int(result) |> print_endline;
    "state " ++ string_of_int(state) |> print_endline;
};

let () = {
    open OptionMonad.Make;
    open OptionMonad.Ex;

    let greaterThanFive = x => make(x > 5 ? Some(x * 2) : None);
    let greaterThanTen = x => make(x > 10 ? Some(x * 2) : None);
    let process = greaterThanFive >=> greaterThanTen;

    let res = process(2) |> extract
    
    switch res {
        | Some(x) => string_of_int(x) |> print_endline
        | None => print_endline("None")
    };
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