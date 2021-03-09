#!/usr/bin/env python
# -*- coding: utf-8 -*-

# FCFS:先到先得
def FCFS(进程集):
  """ 进程集: ((到1,耗1,级1),(到2,耗2,级2)))
      到: 到达时间
      耗: 运行时间
      级: 优先级, 用不到
  """
  

def decrypt(cipher, key):
    """ decryption
        cipher --- cipher text
        key    --- symmetric key
    """
    blocksize = len(key)
    msglen = len(cipher)
    if msglen % blocksize != 0:
        print("bad key!")
        return
    
    numblocks = msglen // blocksize
    pblk = ['0']*blocksize
    plain=[]
    for b in range(numblocks):
        for i in range(blocksize):
            pblk[int(key[i])-1]=cipher[b*blocksize + i]
        plain.extend(pblk)

    return "".join(plain)    
        

def demo(plaintext, key):
    # print("original plaintext:", plain)
    cipher = encrypt(plain, key)
    print(cipher)
    
    #test decryption
    decrypted_plain = decrypt(cipher, key)
    print(decrypted_plain)
        
if __name__ == '__main__':
    # test encryption
    plain = "on#the#mountain"
    key='31425'
    demo(plain,key)
