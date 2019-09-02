module TestReaderMonad = ReaderMonad.Make({ type t = (string, string); });

module TestReaderMonadEx = Monad.Ex(TestReaderMonad);

let () = {
    open Jest;

    describe("Reader Monad", () => {
        open Expect;
        open TestReaderMonad;
        open TestReaderMonadEx;

        let joinBefore = x => make(((e, _)) => e ++ " " ++ x);
        let joinAfter = x => make(((_, e)) => x ++ " " ++ e);

        test("fish", () => {
            let process = joinBefore >=> joinAfter;

            let result = ("Left", "Right") |> (process("Between") |> extract);

            expect(result) |> toEqual("Left Between Right");
        });

        test("bind", () => {
            let monad = return("Between") >>= joinBefore >>= joinAfter;

            let result =  ("Left", "Right") |> (monad |> extract);

            expect(result) |> toEqual("Left Between Right");
        });
    });
};