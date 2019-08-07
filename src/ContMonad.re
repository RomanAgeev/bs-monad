module type T = {
    include Monad.T;

    type r;

    let make: (('a => r) => r) => t('a);
    let extract: t('a) => (('a => r) => r);
};

module Make = (R: { type t; }): (T with type r := R.t) => {
    type t('a) = ('a => R.t) => R.t;

    let bind = (kx, f) => hy => kx(x => f(x)(hy));
    let return = x => f => f(x);

    let make = x => x;
    let extract = x => x;
};
