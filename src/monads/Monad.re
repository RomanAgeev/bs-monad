module type T = {
    type t('a);

    let bind: (t('a), 'a => t('b)) => t('b);
    let return: 'a => t('a);
};

module Ex = (M: T) => {
    let (>>=) = M.bind;
    let (>=>) = (f: 'a => M.t('b), g: 'b => M.t('c)): ('a => M.t('c)) => x => f(x) >>= g;
}
