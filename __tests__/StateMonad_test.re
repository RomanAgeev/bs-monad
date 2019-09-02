module TestStateMonad = StateMonad.Make({ type t = string });

module TestStateMonadEx = Monad.Ex(TestStateMonad);

let () = {
    open Jest;

    describe("State Monad", () => {
        open Expect;
        open TestStateMonad;
        open TestStateMonadEx;

        let first = x => make(s => (x ++ " " ++ s, "First"));
        let second = x => make(s => (x ++ " " ++ s, "Second"));

        test("fish", () => {
            let process = first >=> second;

            let (value, state) = "Init" |> (process("Value") |> extract);

            expect((value, state)) |> toEqual(("Value Init First", "Second"));
        });

        test("bind", () => {
            let monad = return("Value") >>= first >>= second;

            let (value, state) = "Init" |> (monad |> extract);

            expect((value, state)) |> toEqual(("Value Init First", "Second"));
        });
    });
};