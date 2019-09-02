module TestPromiseMonad = PromiseMonad.Make;
module TestPromiseMonadEx = PromiseMonad.Ex;

exception Test_Error(string);

let () = {
    open Jest;

    describe("Promise Monad", () => {
        open Expect;
        open TestPromiseMonad;
        open TestPromiseMonadEx;

        let double = x => return(x * 2);
        let triple = x => return(x * 3);
        let increment = x => return(x + 1);

        testPromise("fish succeed", () => {
            let process = double >=> increment;

            process(10)
                >>= (x => return(expect(x) |> toEqual(21)))
                |> extract;
        });

        testPromise("bind succeed", () =>
            return(10)
                >>= double
                >>= increment
                >>= (x => return(expect(x) |> toEqual(21)))
                |> extract);

        testPromise("failed", () =>
            return(10)
                >>= double
                >>= increment
                >>= (x => throw(Test_Error({j|Error with $x|j})))
                >>= triple
                >>| (_error => return([%raw "_error[1]"]))
                >>= (x => return({j|$x|j}))
                >>= (x => return(expect(x) |> toEqual("Error with 21")))
                |> extract)
        
    });
};
