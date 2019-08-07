module type T = {
    include Monad.T;

    let make: 'a => t('a);
    let extract: t('a) => 'a;
};

module Make: T = {
    type t('a) = 'a;

    let bind = (x, f) => f(x);
    let return = x => x;

    let make = x => x;
    let extract = x => x;
};
