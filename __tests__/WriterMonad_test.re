module TestWriterMonad = WriterMonad.Make({
    type t = string;

    let mappend = (s1, s2) => s1 ++ ", then " ++ s2;
    let mempty = () => "";
});

module TestWriterMonadEx = Monad.Ex(TestWriterMonad);

let () = {
    open Jest;

    describe("Writer Monad", () => {
        open Expect;
        open TestWriterMonad;
        open TestWriterMonadEx;

        let mult = x => make((x * 2, "Multiply by 2"));
        let plus = x => make((x + 2, "Plus 2")); 

        test("fish", () => {
            let process = mult >=> plus;

            let result = process(10) |> extract;

            expect(result) |> toEqual((22, "Multiply by 2, then Plus 2"));
        });

        test("bind", () => {
            let monad = make((10, "Take 10")) >>= mult >>= plus;
            
            let result = monad |> extract; 

            expect(result) |> toEqual((22, "Take 10, then Multiply by 2, then Plus 2"));
        });
    });
};
