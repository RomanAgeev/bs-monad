module type T = (M: Monoid.T) => {
    include Monad.T;

    let make: ('a, M.t) => t('a);
    let extract: t('a) => ('a, M.t);
}

module Make: T = (M: Monoid.T) => {
    type t('a) = ('a, M.t);

    let bind = (x, f) => {
        let (v, m) = x;
        let (v', m') = f(v);
        (v', M.mappend(m, m'))
    };
    let return = x => (x, M.mempty());

    let make = (x, y) => (x, y);
    let extract = ((x, y)) => (x, y);
};
