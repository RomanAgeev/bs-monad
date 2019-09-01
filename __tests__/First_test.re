open Jest;

describe("First", () => {
    open Expect;

    test("tobe", () => expect(1 + 2) |> toBe(3));
});