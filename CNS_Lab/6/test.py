#!/usr/bin/env python

# These test vectors are from the Project NESSIE http://goo.gl/xSpWfg

TEST_VECTORS = (
    (
        0x80000000000000000000000000000000,  # key
        0x0000000000000000,  # plain
        0xb1f5f7f87901370f,  # cipher
    ), (
        0x40000000000000000000000000000000,
        0x0000000000000000,
        0xb3927dffb6358626,
    )
)



def main():
    from idea import IDEA
    my_cipher = IDEA(0)

    for test in TEST_VECTORS:
        print test
        key, plain, cipher = test
        my_cipher.change_key(key)
        encrypted = my_cipher.encrypt(plain)
        assert encrypted == cipher
    print 'All passed!'


if __name__ == '__main__':
    main()
