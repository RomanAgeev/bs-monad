module TestOptionMonad = OptionMonad.Make;

module TestOptionMonadEx = Monad.Ex(TestOptionMonad);

let () = {
    open Jest;

    describe("Option Monad", () => {
        open Expect;
        open TestOptionMonad;
        open TestOptionMonadEx;

        let first = x => make(Some(x ++ " " ++ "First"));
        let second = x => make(Some(x ++ " " ++ "Second"));
        let fail = _ => make(None);

        test("fish success", () => {
            let process = first >=> second;

            let result = process("Value") |> extract;

            expect(result) |> toEqual(Some("Value First Second"));
        });

        test("fish fail first", () => {
            let process = fail >=> first >=> second;

            let result = process("Value") |> extract;

            expect(result) |> toEqual(None);
        });

        test("fish fail last", () => {
            let process = first >=> second >=> fail;

            let result = process("Value") |> extract;

            expect(result) |> toEqual(None);
        });

        test("bind success", () => {
            let monad = return("Value") >>= first >>= second;

            let result = monad |> extract;

            expect(result) |> toEqual(Some("Value First Second"));
        });

        test("bind fail first", () => {
            let monad = return("Value") >>= fail >>= first >>= second;

            let result = monad |> extract;

            expect(result) |> toEqual(None);
        });

        test("bind fail last", () => {
            let monad = return("Value") >>= first >>= second >>= fail;

            let result = monad |> extract;

            expect(result) |> toEqual(None);
        });
    });
};