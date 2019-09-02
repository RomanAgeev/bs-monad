module TestContMonad = ContMonad.Make({ type t = int });

module TestContMonadEx = Monad.Ex(TestContMonad);

let () = {
    open Jest;

    describe("Cont Monad", () => {
        open Expect;
        open Utils;
        open TestContMonad;
        open TestContMonadEx;

        let square = f => return(x => f(x * x));
        let increment = f => return(x => f(x + 1));
        let four = f => f(4);

        test("fish", () => {
            let process = increment >=> square;

            let result = four |> (process(id) |> extract);

            expect(result) |> toEqual(17);
        });

        test("bind", () => {
            let monad = return(id) >>= increment >>= square;

            let result = four |> (monad |> extract);

            expect(result) |> toEqual(17);
        });
    });
};
