open Utils;

module type T = {
    include Monad.T;

    let make: 'a => t('a);
    let extract: t('a) => 'a;
};

module Make: T = {
    type t('a) = 'a;

    let bind = (x, f) => f(x);
    let return = id;
    let make = id;
    let extract = id;
};
