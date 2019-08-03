module type T = {
    include Monad.T;

    type e;

    let make: (e => 'a) => t('a);
    let extract: t('a) => (e => 'a);
};

module Make = (E: { type t; }): (T with type e := E.t) => {
    type t('a) = E.t => 'a;

    let bind = (rx, f) => env => env |> (env |> rx |> f);
    let return = x => _ => x;

    let make = x => x;
    let extract = x => x;
};
