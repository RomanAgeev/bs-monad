open Utils;

module type T = {
    include Monad.T;

    type s;

    let make: (s => ('a, s)) => t('a);
    let extract: t('a) => (s => ('a, s));
};

module Make = (S: { type t; }): (T with type s := S.t) => {
    type t('a) = S.t => ('a, S.t);

    let bind = (sx, f) => st => {
        let (x, st') = sx(st);
        st' |> (x |> f);
    };
    let return = x => st => (x, st);
    let make = id;
    let extract = id;
};
