import pathlib,tempfile,subprocess
with tempfile.TemporaryDirectory()as tmp:
    p=pathlib.Path(tmp)/'data';p.write_bytes(b'banana\nban\x00banana')
    out=subprocess.check_output(['./app','ana',str(p)],text=True);assert out.splitlines()==['1:1','1:3','2:12','2:14','matches=4'],out
    p.write_bytes(b'');assert subprocess.check_output(['./app','x',str(p)],text=True).strip()=='matches=0'
print('Overlapping matches, line/byte offsets, binary data, and empty file passed')
