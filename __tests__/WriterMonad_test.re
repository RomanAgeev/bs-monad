module TestWriterMonad = WriterMonad.Make({
    type t = string;

    let mappend = (s1, s2) => s1 ++ " then " ++ s2;
    let mempty = () => "";
});

module TestWriterMonadEx = Monad.Ex(TestWriterMonad);

let () = {
    open Jest;

    describe("Writer Monad", () => {
        open Expect;
        open TestWriterMonad;
        open TestWriterMonadEx;

        test("test", () => {
            let mult = x => make((x * 2, "Multiply by 2"));
            let plus = x => make((x + 2, "Plus 2"));
            let process = mult >=> plus;

            let result = process(10) |> extract;
            // string_of_int(res) |> print_endline;
            // print_endline(log);

            expect(result) |> toBe((22, "Multiply by 2 then Plus 2"));
        });
    });
};
