module TestListMonad = ListMonad.Make;

module TestListMonadEx = Monad.Ex(TestListMonad);

let () = {
    open Jest;

    let enum = (count: int) => {
        let rec aux = (~result=[], index: int) => index == 0 ? result : aux(~result=[index, ...result], index - 1);
        aux(count);
    };

    describe("List Monad", () => {
        open Expect;
        open Utils;
        open TestListMonad;
        open TestListMonadEx;

        let enumerate = enum >> make;
        let double = x => return(x * 2);
        let toString = string_of_int >> return;

        test("fish", () => {
            let process = enumerate >=> double >=> toString;

            let result = process(3) |> extract;

            expect(result) |> toEqual(["2", "4", "6"]);
        });

        test("bind", () => {
            let monad = enumerate(3) >>= double >>= toString;

            let result = monad |> extract;

            expect(result) |> toEqual(["2", "4", "6"]);
        });
    });
};