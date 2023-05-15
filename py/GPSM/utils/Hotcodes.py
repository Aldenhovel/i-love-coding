import selenium
from selenium import webdriver
from selenium.webdriver.common.by import By
import re
import datetime

from selenium.webdriver.chrome.options import Options

def get_hotcodes():
    chrome_options = Options()
    chrome_options.add_experimental_option("debuggerAddress", "127.0.0.1:9222")
    driver = webdriver.Chrome(options=chrome_options)
    url = """http://www.iwencai.com/unifiedwap/result?w=%E6%88%90%E4%BA%A4%E9%A2%9D%E9%AB%98%E4%B8%94%E9%9D%9E%E6%B6%A8%E5%81%9C%E4%B8%94%E9%9D%9Est%E4%B8%94%E9%9D%9E%E8%B7%8C%E5%81%9C%E4%B8%94%E6%B6%A8%E8%B7%8C%E5%B9%85%E5%B0%8F%E4%BA%8E10%25%E4%B8%94%E6%8C%AF%E5%B9%85%E5%B0%8F%E4%BA%8E10%25&querytype=stock
    """
    driver.get(url)
    flag = False
    while not flag:
        try:
            table = driver.find_element(By.XPATH, '//*[@id="iwc-table-container"]/div[5]/div[2]/div[2]/div/table/tbody')
            flag = True
        except Exception as e:
            pass

    codes = table.text.split("\n")
    codes = [*filter(lambda x: re.match(r"[0|3|6][0-9]{5}", x), codes)]
    print(f"[{datetime.datetime.now()}] {len(codes)} codes was found.")
    return codes