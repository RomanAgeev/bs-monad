open Utils;

module type T = {
    include Monad.T;

    type m;

    let make: (('a, m)) => t('a);
    let extract: t('a) => ('a, m);
}

module Make = (M: Monoid.T): (T with type m := M.t) => {
    type t('a) = ('a, M.t);

    let bind = (x, f) => {
        let (v, m) = x;
        let (v', m') = f(v);
        (v', M.mappend(m, m'))
    };
    let return = x => (x, M.mempty());
    let make = id;
    let extract = id;
};
