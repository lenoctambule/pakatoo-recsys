from socketipc import *
import unittest

class MessageBuilderTest(unittest.TestCase):

    def test_string(self):
        msg = Message(0, 0, b"salut ca va")
        ret = msg.build_msg()
        self.assertEqual(ret, b'\x00\x00\x00\x00\x0b\x00\x00\x00\x00\x00\x00\x00salut ca va')

if __name__ == "__main__" :
    unittest.main()