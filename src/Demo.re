exception Test_Error(string);

let () = {
    open Monad.PromiseMonad;

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