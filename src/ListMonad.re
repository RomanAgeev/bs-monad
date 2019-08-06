module type T = {
    include Monad.T;

    let make: list('a) => t('a);
    let extract: t('a) => list('a);
};

module Make: T = {
    type t('a) = list('a);

    let bind = (li, f) => List.(li |> map(f) |> flatten);
    let return = x => [x];

    let make = x => x;
    let extract = x => x;
};

module Ex = Monad.Ex(Make);