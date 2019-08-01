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

    let double = x => make(x * 2, " Double");
    let tripple = x => make(x * 3, " Tripple");
    let process = double >=> tripple;

    let (x, log) = process(2) |> extract;

    string_of_int(x) |> print_endline;
    print_endline(log);
};